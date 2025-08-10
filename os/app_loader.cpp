#include <Arduino.h>
#include "app_header.h"

/**
 * Assumptions:
 *  * Bootloader resides within the first 1 MB of flash
 *  * The application resides at a specific memory location in flash (0x10000000 + 1MB)
 *  * It contains a small app header with metadata (see app_header.h)
 */
bool startup_app() {
    // Load app header from flash
    app_header_t* app_header = (app_header_t*)0x10000000 + 0x100000; // 1 MB offset
    if (app_header->magic != APP_HEADER_MAGIC) {
        Serial.println("Invalid app header magic");
        return false;
    }
    Serial.print("Loading app: ");
    Serial.write((const uint8_t*) app_header->name, strnlen(app_header->name, sizeof(app_header->name)));
    Serial.println(
        " (version: " + String(app_header->version >> 16) + "." +
        String((app_header->version >> 8) & 0xFF) + "." +
        String(app_header->version & 0xFF) + ")"
    );
    // extract entry point
    void (*app_entry_point)(void) = (void (*)(void))(app_header->entry_point);
    // Print it
    Serial.print("Entry point: 0x");
    Serial.println(app_header->entry_point, HEX);
    // Check if entry point is valid (flash is only 16MB, first 1MB is OS, so it has to be in a certain range)
    if (app_entry_point < (void (*)(void))0x10000000 || app_entry_point >= (void (*)(void))0x11000000) {
        Serial.println("Invalid entry point address");
        return false;
    }
    Serial.println("Application entry point is valid, starting application...");
    Serial.flush();
    // Call the application entry point
    app_entry_point();
    return true;
}