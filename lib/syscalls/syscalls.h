#ifndef _SYSCALLS_H_
#define _SYSCALLS_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  @brief Perform a system call.
 *  @param svc_num The system call number.
 *  @param arg Pointer to the argument for the system call.
 */
#pragma GCC push_options
#pragma GCC optimize("Os")
static inline int syscall(int svc_num, void* arg) {
    register int r0 asm("r0") = (int)arg;   // argument pointer
    register int r1 asm("r1") = svc_num;    // syscall number
    asm volatile (
        "svc #0\n"
        : "+r"(r0)         // return value in r0
        : "r"(r1)
        : "memory"
    );
    return r0;
}
#pragma GCC pop_options

typedef enum {
    SYSCALL_PRINT = 0,
    SYSCALL_EXIT,
    // Add more syscalls here as needed
} syscall_number_t;

#ifdef __cplusplus
}
#endif

#endif // _SYSCALLS_H_