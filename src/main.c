#include "attach.h"
#include <windows.h>
#include "api_request.h"
#include "config.h"

int main() {
    while (1 > 0) {
        if (verification() == 1) {
            Sleep(100000);
        } else {
            printf("No rabbit found! What can we do...");
            EnvVars env = load_env();
            send_message(env);
            Sleep(100000);
        }
    }
}