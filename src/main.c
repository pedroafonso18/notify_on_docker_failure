#include "attach.h"
#include <windows.h>

int main() {
    while (1 > 0) {
        if (verification() == 1) {
            Sleep(1000000000);
        } else {
            printf("No rabbit found! What can we do...");
            Sleep(1000000000);
        }
    }
}