#include "attach.h"

typedef struct {
    int found;
    char* process_name;
} ProcessStatus;

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

    // Allocate array to track status of each process
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
        
        // Check each process against the current line
        for(int i = 0; i < cfg->process_count; i++) {
            if (strstr(lower_path, cfg->processes[i]) != NULL) {
                status[i].found = 1;
            }
        }
    }

    pclose(processes);
    
    // Print status for each process
    int any_missing = 0;
    for(int i = 0; i < cfg->process_count; i++) {
        if (!status[i].found) {
            printf("Container not found: %s\n", status[i].process_name);
            any_missing = 1;
        }
    }
    
    if (!any_missing) {
        printf("All containers are running!\n");
    }

    // Don't free cfg here as we're still using its process names
    return status;
}

void free_process_status(ProcessStatus* status) {
    if (status) {
        free(status);
    }
}