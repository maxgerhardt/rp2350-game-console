#ifndef _SYSCALLS_H_
#define _SYSCALLS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/**
 * @brief System call numbers for the Game OS.
 */
typedef enum {
    /* Subsystem: Console I/O */
    SYSCALL_PRINTSTR = 0,
    SYSCALL_WRITE = 1,
    SYSCALL_FLUSH = 2,
    SYSCALL_READ = 3,
    SYSCALL_READ_TIMEDOUT = 4,
    /* Subsystem: Application Control */
    SYSCALL_EXIT,
    /* Subsystem: File Access */
    SYSCALL_FILE_OPEN,
    SYSCALL_FILE_READ,
    SYSCALL_FILE_WRITE,
    SYSCALL_FILE_SEEK,
    SYSCALL_FILE_TELL,
    SYSCALL_FILE_SIZE,
    SYSCALL_FILE_STAT,
    SYSCALL_FILE_CLOSE,
    /* Subsystem: LED Control */
    SYSCALL_LED_SET_COLOR,
    /* Subsystem: Gamepad Input */
    SYSCALL_GAMEPAD_GET_STATE,
    /* Subystem: Basic Graphics */
    SYSCALL_GRAPHICS_INIT,
    SYSCALL_GRAPHICS_CLEAR,
    SYSCALL_GRAPHICS_DRAW_PIXEL,
    SYSCALL_GRAPHICS_DRAW_LINE,
    SYSCALL_GRAPHICS_DRAW_RECT,
    SYSCALL_GRAPHICS_FILL_RECT,
    SYSCALL_GRAPHICS_DRAW_CIRCLE,
    SYSCALL_GRAPHICS_FILL_CIRCLE,
    SYSCALL_GRAPHICS_DRAW_TEXT,
    SYSCALL_GRAPHICS_DRAW_IMAGE,
    /* Subystem: Basic Audio */
    SYSCALL_AUDIO_PLAY_SOUND,
    SYSCALL_AUDIO_PAUSE_SOUND,
    SYSCALL_AUDIO_RESUME_SOUND,
    SYSCALL_AUDIO_CLOSE_SOUND,
    SYSCALL_AUDIO_SET_VOLUME,
    SYSCALL_AUDIO_GET_VOLUME,    
    /* Subsystem: RTC */
    SYSCALL_RTC_GET_TIME,
    /* Subsystem: Savegame */
    SYSCALL_SAVEGAME_CREATE,
    SYSCALL_SAVEGAME_LOAD,
    SYSCALL_SAVEGAME_DELETE,
    SYSCALL_SAVEGAME_LIST,
    /* Subsystem: Game engine functionality */
    SYSCALL_RESOURCE_LOAD, // Load a resource (image, sound, etc.)
    SYSCALL_RESOURCE_UNLOAD, // Unload a resource
    SYSCALL_RESOURCE_GET_INFO, // Get information about a resource
    SYSCALL_GAME_OBJECT_CREATE, // Create a game object (with a behavior script and a position by default)
    SYSCALL_GAME_OBJECT_DESTROY, // Destroy a game object
    SYSCALL_GAME_OBJECT_ADD_SPRITE, // Add a sprite to a game object
    SYSCALL_GAME_OBJECT_ADD_COLIDER, // Add a collider to a game object
    SYSCALL_GAME_OBJECT_ADD_SOUND, // Add a sound to a game object
    SYSCALL_CAMERA_SET_POSITION, // Set camera position
    SYSCALL_CAMERA_GET_POSITION, // Get camera position
    SYSCALL_UI_CREATE_ELEMENT, // Create a UI element (button, label, etc.)
    SYSCALL_UI_DESTROY_ELEMENT, // Destroy a UI element   
    SYSCALL_UI_SET_TEXT, // Set text of a UI element
    SYSCALL_UI_SET_POSITION, // Set position of a UI element
    SYSCALL_UI_SET_SIZE, // Set size of a UI element
    SYSCALL_UI_SET_COLOR, // Set color of a UI element
    SYSCALL_UI_SET_VISIBLE, // Set visibility of a UI element
    SYSCALL_UI_SET_INTERACTIVE, // Set if a UI element is interactive
    SYSCALL_UI_SET_ON_CLICK, // Set callback for click event on a UI element
    /* Subystem: Network connectivity */
    SYSCALL_NETWORK_GET_INFO, /* is connected, on what interface, what IP, ... */
    /* Subsystem: HTTP network services */
    SYSCALL_HTTP_GET,
    SYSCALL_HTTP_POST,
    SYSCALL_HTTP_PUT,
    SYSCALL_HTTP_DELETE,
    /* Subystem: Account management */
    SYSCALL_ACCOUNT_GET_CONSOLE_UUID,
    SYSCALL_ACCOUNT_IS_LOGGED_IN,
    SYSCALL_ACCOUNT_GET_USER_INFO, // including friend code etc
    SYSCALL_ACCOUNT_GET_FRIENDS_LIST,
    SYSCALL_ACCOUNT_SEND_FRIEND_REQUEST,
    SYSCALL_ACCOUNT_GET_FRIEND_REQUESTS,
    SYSCALL_ACCOUNT_REMOVE_FRIEND,
    SYSCALL_ACCOUNT_ACCEPT_FRIEND_REQUEST,
    SYSCALL_ACCOUNT_REJECT_FRIEND_REQUEST,
    SYSCALL_ACCOUNT_SEND_MESSAGE_TO_FRIEND,
    SYSCALL_ACCOUNT_GET_MESSAGES_FROM_FRIENDS,
    // Add more syscalls here as needed
    SYSCALL_MAX
} syscall_number_t;

/**
 * @brief Print a null-terminated string to the console.
 * @param str The string to print.
 * @return The number of characters printed.
 */
int syscall_printstr(const char* str);

/**
 * @brief Write data to the console.
 * @param buffer Pointer to the data to write.
 * @param length Number of bytes to write.
 * @return The number of bytes written.
 */
int syscall_write(const uint8_t* buffer, uint32_t length);

/**
 * @brief Flush the console output.
 * @return 0 on success.
 */
int syscall_flush(void);

/** 
 * @brief Blocking read from console.
 * @param buffer Pointer to the buffer to read data into.
 * @param length Number of bytes to read.
 * @return The number of bytes read.
 */
int syscall_read(uint8_t* buffer, uint32_t length);

/**
 * @brief Read data from console with a timeout.
 * @param buffer Pointer to the buffer to read data into.
 * @param length Number of bytes to read.
 * @param timeout_ms Timeout in milliseconds. 
 * @return The number of bytes read
 */
int syscall_read_timedout(uint8_t* buffer, uint32_t length, uint32_t timeout_ms);

/**
 * @brief Exit the application with a specific exit code.
 * @param exit_code The exit code to return.
 * @note Does not return
 */
int syscall_exit(int exit_code);

/**
 *  @brief Perform a system call.
 *  @param syscall_num The system call number.
 *  @param arg Pointer to the argument for the system call.
 */
#pragma GCC push_options
#pragma GCC optimize("Os")
static inline int syscall(int syscall_num, void* arg) {
    register int r0 asm("r0") = (int)arg;    // argument pointer
    register int r1 asm("r1") = syscall_num; // syscall number
    asm volatile (
        "svc #0\n"
        : "+r"(r0)         // return value in r0
        : "r"(r1)
        : "memory"
    );
    return r0;
}
#pragma GCC pop_options

#ifdef __cplusplus
}
#endif

#endif // _SYSCALLS_H_