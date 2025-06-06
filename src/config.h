#ifndef CONFIG_H
#define CONFIG_H

#include <stdio.h>
#include <stdbool.h>

typedef struct {
    char* xauth;
    char* xuser;
} EnvVars;

typedef struct {
    char** processes;
    bool enabled;
    int process_count;
} ConfigData;

EnvVars load_env(void);
void* get_config(void);
void free_config(void* config);

#endif