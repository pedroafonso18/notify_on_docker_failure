#include "attach.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int verification(void) {
    FILE* processes;
    char path[1035];
    int found_rabbit = 0;
    
    processes = popen("docker ps", "r");
    if (processes == NULL) {
        printf("Failed to run command\n");
        return -1;
    }

    printf("Checking for RabbitMQ containers...\n");
    while (fgets(path, sizeof(path) - 1, processes) != NULL) {
        printf("%s", path);
        char lower_path[1035];
        strcpy(lower_path, path);
        for(int i = 0; lower_path[i]; i++) {
            lower_path[i] = tolower(lower_path[i]);
        }
        
        if (strstr(lower_path, "rabbit") != NULL) {
            found_rabbit = 1;
        }
    }

    pclose(processes);
    
    if (!found_rabbit) {
        printf("No RabbitMQ containers found running!\n");
    } else {
        printf("Found RabbitMQ container(s)\n");
    }
    
    return found_rabbit;
}