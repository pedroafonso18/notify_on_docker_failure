#include <stdlib.h>
#include "../include/dotenv.h"
#include "config.h"

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