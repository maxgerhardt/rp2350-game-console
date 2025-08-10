#include <Arduino.h>
#include "syscalls.h"
#define LED LED_BUILTIN

void setup() {
    pinMode(LED, OUTPUT);
    Serial.begin(115200);
}

void loop() {
    digitalWrite(LED, HIGH);
    delay(1000);
    digitalWrite(LED, LOW);
    delay(1000);
    // test out print syscall
    const char* message = "Hello from RP2350!";
    int ret = syscall(SYSCALL_PRINT, (void*)message);
    Serial.println("Syscall print returned: " + String(ret));
}