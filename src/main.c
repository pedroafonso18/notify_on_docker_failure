#include "attach.h"
#include "api_request.h"
#include "config.h"
#include <unistd.h>

int main() {
    while (1) {
        ProcessStatus* status = verification();
        
        if (status != NULL) {
            ConfigData* cfg = get_config();
            int any_missing = 0;
            
            for (int i = 0; i < cfg->process_count; i++) {
                if (!status[i].found) {
                    any_missing = 1;
                    EnvVars env = load_env();
                    char message[256];
                    snprintf(message, sizeof(message), "Container not found: %s", status[i].process_name);
                    send_message(env, message);
                }
            }
            
            free_process_status(status);
            free_config(cfg);
            
            usleep(100000000);
        } else {
            usleep(5000000);
        }
    }
    
    return 0;
}