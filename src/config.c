#include "config.h"
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "../include/toml.h"
#include "../include/dotenv.h"

EnvVars load_env() {
    if (env_load("../.env", false) != 0) {
        EnvVars vars = {NULL, NULL};
        return vars;
    }

    EnvVars vars;
    vars.xauth = getenv("XAUTH");
    vars.xuser = getenv("XUSER");

    return vars;
}

void* get_config() {
    FILE* fp;
    char errbuf[200];

    fp = fopen("../config.toml","r");
    if (!fp) {
        fprintf(stderr, "ERROR: Cannot open config.toml - %s", strerror(errno));
        exit(1);
    }

    toml_table_t* conf = toml_parse_file(fp, errbuf, sizeof(errbuf));
    fclose(fp);

    if (!conf) {
        fprintf(stderr, "ERROR: Cannot parse - %s", strerror(errno));
        exit(1);
    }

    toml_table_t* list_table = toml_table_in(conf, "list");
    if (!list_table) {
        fprintf(stderr, "ERROR: Missing [list] in toml file.");
        exit(1);
    }

    toml_datum_t enabled = toml_bool_in(list_table, "enabled");
    if (!enabled.ok) {
        fprintf(stderr, "ERROR: Missing \"enabled\" in toml file.");
        exit(1);
    }

    toml_datum_t restart = toml_bool_in(list_table, "restart");
    if (!restart.ok) {
        fprintf(stderr, "ERROR: Missing \"restart\" in toml file.");
    }

    toml_datum_t send_message = toml_bool_in(list_table, "send_message");
    if (!restart.ok) {
        fprintf(stderr, "ERROR: Missing \"send_message\" in toml file.");
    }


    toml_array_t* processes_array = toml_array_in(list_table, "processes");
    if (!processes_array) {
        fprintf(stderr, "ERROR: Missing \"processes\" array in the [list] table.");
        exit(1);
    }

    int array_size = toml_array_nelem(processes_array);
    
    ConfigData* config_data = malloc(sizeof(ConfigData));
    config_data->processes = malloc(sizeof(char*) * array_size);
    config_data->process_count = array_size;
    config_data->enabled = enabled.u.b;
    config_data->restart = restart.u.b;
    config_data->send_message = send_message.u.b;

    for (int i = 0; i < array_size; i++) {
        toml_datum_t process = toml_string_at(processes_array, i);
        if (!process.ok) {
            fprintf(stderr, "ERROR: Invalid process at index %d", i);
            exit(1);
        }
        config_data->processes[i] = strdup(process.u.s);
        free(process.u.s);
    }

    toml_free(conf);

    return config_data;
}

void free_config(void* config) {
    if (config) {
        ConfigData* config_data = (ConfigData*)config;
        for (int i = 0; i < config_data->process_count; i++) {
            free(config_data->processes[i]);
        }
        free(config_data->processes);
        free(config_data);
    }
}