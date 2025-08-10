#ifndef _SVC_HANDLER_H_
#define _SVC_HANDLER_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Service Call (SVC) handler for the RP2350 game console OS.    
 */
typedef int (*syscall_t)(void*);

/**
 * @brief Prints a string to the console.
 * @param arg Pointer to the string to print.
 * @return Number of characters printed.
 */
int syscall_print(void* arg);

/**
 * @brief Exits the application with a given exit code.
 * @param arg Pointer to the exit code (int).
 * @return 0 (should not reach here).
 */
int syscall_exit(void* arg);

#ifdef __cplusplus
}
#endif

#endif // _SVC_HANDLER_H_