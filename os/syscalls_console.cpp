#include <Arduino.h>
#include "svc_handler.h"

int syscall_print(void* arg) {
    const char* str = (const char*)arg;
    return (int) Serial.println(str);
}

int syscall_exit(void* arg) {
    int exit_code = (int)(intptr_t)arg;
    Serial.print("Exited with code: ");
    Serial.println(exit_code);
    Serial.flush();
    // Perform any necessary cleanup here
    //while (true); // halt the system
    return 0; // should not reach here
}