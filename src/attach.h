#ifndef ATTACH_H
#define ATTACH_H

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "config.h"

typedef struct {
    int found;
    char* process_name;
} ProcessStatus;

ProcessStatus* verification(void);
void free_process_status(ProcessStatus* status);
void restart_process(ProcessStatus* status);

#endif