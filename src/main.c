#include "attach.h"
#include "api_request.h"
#include "config.h"
#include <unistd.h>
#include <time.h>

int main() {
    while (1) {
        ProcessStatus* status = verification();
        
        if (status != NULL) {
            ConfigData* cfg = get_config();
            
            for (int i = 0; i < cfg->process_count; i++) {
                if (!status[i].found) {
                    EnvVars env = load_env();
                    send_message(env, status[i].process_name);
                }
            }
            
            free_process_status(status);
            free_config(cfg);
            
            sleep(100);
        } else {
            sleep(5);
        }
    }
    
    return 0;
}