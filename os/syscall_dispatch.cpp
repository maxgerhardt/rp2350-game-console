#include "syscall_dispatch.h"
#include "syscalls.h"

int syscall_dispatch(int syscall_num, uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4) {
    // Check if the syscall number is valid
    if (syscall_num < 0 || syscall_num >= SYSCALL_MAX) {
        return -1; // Invalid syscall number
    }

    // Call the appropriate syscall handler
    switch (syscall_num) {
        case SYSCALL_PRINTSTR:
            return syscall_printstr((const char *)arg1);
        case SYSCALL_WRITE:
            return syscall_write((const uint8_t *)arg1, (uint32_t)arg2);
        case SYSCALL_FLUSH:
            return syscall_flush();
        case SYSCALL_READ:
            return syscall_read((uint8_t *)arg1, (uint32_t)arg2);
        case SYSCALL_READ_TIMEDOUT:
            return syscall_read_timedout((uint8_t *)arg1, (uint32_t)arg2, (uint32_t)arg3);        
        case SYSCALL_EXIT:
            return syscall_exit((int)arg1);
        // Add more syscalls here as needed
        default:
            // Unknown syscall (should be unreachable since number of syscalls is checked above)
            return -1; 
    }
}