#include "attach.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int restart_process(ProcessStatus* status) {
    char* start_string = "docker start " + *status->process_name;  
    FILE* start = popen(start_string, "r");
    if (start == NULL) {
        printf("Failed to run command\n");
        return -1;
    }
    return 1;
}

ProcessStatus* verification(void) {
    FILE* processes;
    char path[1035];
    ConfigData* cfg = get_config();

    if (!cfg->enabled) {
        printf("Verification is not enabled, waiting...\n");
        free_config(cfg);
        return NULL;
    }

    processes = popen("docker ps", "r");
    if (processes == NULL) {
        printf("Failed to run command\n");
        free_config(cfg);
        return NULL;
    }

    ProcessStatus* status = malloc(sizeof(ProcessStatus) * cfg->process_count);
    for (int i = 0; i < cfg->process_count; i++) {
        status[i].found = 0;
        status[i].process_name = cfg->processes[i];
    }

    printf("Checking for containers...\n");
    while (fgets(path, sizeof(path) - 1, processes) != NULL) {
        char lower_path[1035];
        strcpy(lower_path, path);
        for(int i = 0; lower_path[i]; i++) {
            lower_path[i] = tolower(lower_path[i]);
        }
        
        for(int i = 0; i < cfg->process_count; i++) {
            if (strstr(lower_path, cfg->processes[i]) != NULL) {
                status[i].found = 1;
            }
        }
    }

    pclose(processes);
    
    int any_missing = 0;
    for(int i = 0; i < cfg->process_count; i++) {
        if (!status[i].found) {
            printf("Container not found: %s\n", status[i].process_name);
            if (cfg->restart) {
                int rst_status = restart_process(&status[i]);
                if (rst_status == 1) {
                    printf("Successfully restarted application!");
                } else {
                    printf("Application restart not successfull.");
                }
            }
            any_missing = 1;
        }
    }
    
    if (!any_missing) {
        printf("All containers are running!\n");
    }

    return status;
}

void free_process_status(ProcessStatus* status) {
    if (status) {
        free(status);
    }
}

