#ifndef CONFIG_H
#define CONFIG_H
#include "../include/dotenv.h"

typedef struct {
    const char* xauth;
    const char* xuser;
} EnvVars;

EnvVars load_env();

#endif