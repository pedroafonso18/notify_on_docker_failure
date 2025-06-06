#ifndef API_REQUEST_H
#define API_REQUEST_H

#include <curl/curl.h>
#include "config.h"

int send_message(EnvVars vars, const char* container_name);

#endif