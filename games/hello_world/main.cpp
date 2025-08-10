#include "syscalls.h"
#include "app_header.h"

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
    syscall(SYSCALL_PRINT, (void*)message);
    syscall(SYSCALL_EXIT, 0);
    return 0;
}