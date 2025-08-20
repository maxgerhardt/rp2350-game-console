#include <Arduino.h>
#include "syscalls.h"

int syscall_printstr(const char* str) {
    return (int) Serial.println(str);
}

int syscall_write(const uint8_t* buffer, uint32_t length) {
    if (buffer == NULL || length == 0) {
        return 0; // Nothing to write
    }
    size_t written = Serial.write(buffer, length);
    return (int) written; // Return number of bytes written
}

int syscall_flush(void) {
    Serial.flush(); // Wait for all data to be sent
    return 0; // Flush does not return a value
}

int syscall_read(uint8_t* buffer, uint32_t length) {
    if (buffer == NULL || length == 0) {
        return 0; // Nothing to read
    }
    // blockingy read data until length is reached without timeout
    size_t bytesRead = 0;
    while (bytesRead < length) {
        size_t this_read = Serial.readBytes(buffer + bytesRead, length - bytesRead);
        if (this_read > 0) {
            bytesRead += this_read;
        } else {
            delay(1); // Wait a bit before trying again
        }
    }
    return (int) bytesRead; // Return number of bytes read
}

int syscall_read_timedout(uint8_t* buffer, uint32_t length, uint32_t timeout_ms) {
    if (buffer == NULL || length == 0) {
        return 0; // Nothing to read
    }
    unsigned long timeoutBefore = Serial.getTimeout();
    Serial.setTimeout(timeout_ms);
    size_t bytesRead = Serial.readBytes(buffer, length);
    Serial.setTimeout(timeoutBefore); // Restore previous timeout
    return (int) bytesRead; // Return number of bytes read
}

int syscall_exit(int exit_code) {
    Serial.print("Exited with code: ");
    Serial.println(exit_code);
    Serial.flush();
    // Perform any necessary cleanup here
    //while (true); // halt the system
    return 0; // should not reach here
}