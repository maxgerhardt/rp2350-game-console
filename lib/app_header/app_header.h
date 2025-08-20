#ifndef _APP_HEADER_H_
#define _APP_HEADER_H_

#include <stdint.h>

#ifndef __cplusplus
extern "C" {
#endif

/**
 * @brief Application header structure.
 * 
 * This structure is used to store metadata about the application
 * that is loaded into the RP2350 game console.
 */
typedef struct {
    uint32_t magic;        // Magic number to identify the header
    uint32_t version;      // Version of the application (in major.minor.patch format, e.g., 0x00010000 for 1.0.0)
    uint32_t entry_point;  // Entry point address of the application
    uint32_t size;         // Size of the application in bytes
    char name[32];         // Name of the application
} app_header_t;

#define APP_HEADER_MAGIC 0xAABBCCDD // Example magic number
#define APP_HEADER_DEFAULT_VERSION 0x00010000 // Default version

#define MAKE_APP_HEADER(app_name, app_version, app_entry_point) \
    __attribute__((section(".app_header"), used)) \
    const app_header_t app_header = { \
        APP_HEADER_MAGIC, \
        (app_version), \
        (uint32_t)(app_entry_point), \
        sizeof(app_header_t), \
        app_name \
    }

#ifndef __cplusplus
}
#endif

#endif // _APP_HEADER_H_