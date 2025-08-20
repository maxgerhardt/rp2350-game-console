#include <Arduino.h>
#include "syscalls.h"
#include "app_loader.h"
#define LED LED_BUILTIN

void setup() {
    pinMode(LED, OUTPUT);
    Serial.begin(115200);
    while(!Serial);
}

void loop() {
    digitalWrite(LED, HIGH);
    delay(1000);
    digitalWrite(LED, LOW);
    delay(1000);
    // test out print syscall
    const char* message = "Hello from RP2350!\r\n";
    int ret = syscall(SYSCALL_PRINTSTR, (void*)message);
    Serial.println("Syscall print returned: " + String(ret));
    startup_app();
}