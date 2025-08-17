#include "syscalls.h"
#include "app_header.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv);
extern "C" void start(void); 

__attribute__((section(".app_header"), used))
const app_header_t my_app_header = {
    APP_HEADER_MAGIC,
    APP_HEADER_DEFAULT_VERSION,
    (uint32_t)start,
    sizeof(app_header_t),
    "Hello World App"
};

int main(int argc, char** argv) {
    (void)argc; // Unused parameter
    (void)argv; // Unused parameter

    const char *message = "Hello, World!\n";
    char buf[64];
    volatile int i = 123;
    snprintf(buf, sizeof(buf), "Message: %d %s", i, message);
    syscall(SYSCALL_PRINT, (void*)buf);
    syscall(SYSCALL_EXIT, 0);

    volatile float f = 3.14f;
    volatile float g = 2*f;

    return 0;
}