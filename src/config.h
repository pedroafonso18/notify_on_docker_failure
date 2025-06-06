#ifndef CONFIG_H
#define CONFIG_H

#include <stdio.h>

typedef struct {
    char* xauth;
    char* xuser;
} EnvVars;

typedef struct {
    char** processes;
    int process_count;
} ConfigData;

EnvVars load_env(void);
void* get_config(void);
void free_config(void* config);

#endif