#ifndef CONFIG_H
#define CONFIG_H
#include "../include/dotenv.h"

typedef struct {
    const char* xauth;
    const char* xuser;
    const char* rid;
} EnvVars;

EnvVars load_env();

#endif