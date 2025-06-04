#include "attach.h"
#include "api_request.h"
#include "config.h"
#include <unistd.h>

int main() {
    while (1 > 0) {
        if (verification() == 1) {
            sleep_ms(100000);
        } else {
            printf("No rabbit found! What can we do...");
            EnvVars env = load_env();
            send_message(env);
            sleep_ms(100000);
        }
    }
}