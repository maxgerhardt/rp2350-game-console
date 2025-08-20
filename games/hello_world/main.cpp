#include "syscalls.h"
#include "app_header.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv);
extern "C" void start(void); 

MAKE_APP_HEADER("Hello World App", APP_HEADER_DEFAULT_VERSION, (uint32_t)start);

int main(int argc, char** argv) {
    (void)argc; // Unused parameter
    (void)argv; // Unused parameter

    const char *message = "Hello, World!\n";
    char buf[64];
    volatile int i = 123;
    snprintf(buf, sizeof(buf), "Message: %d %s", i, message);
    syscall(SYSCALL_PRINTSTR, (void*)buf);
    syscall(SYSCALL_EXIT, 0);

    volatile float f = 3.14f;
    volatile float g = 2*f;

    return 0;
}