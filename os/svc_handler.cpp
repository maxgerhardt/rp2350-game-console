#include <Arduino.h>
#include "syscall_dispatch.h"
#include "syscalls.h"

// This comes from the pico-sdk and "LIB_CMSIS_CORE" and "PICO_CMSIS_RENAME_EXCEPTIONS" turned off
// Otherwise it would be called "SVC_Handler"
#define SVC_HANDLER_FUNC isr_svcall

extern "C" __attribute__((naked)) 
void SVC_HANDLER_FUNC(void) {
    asm volatile (
        "tst lr, #4\n"            // Bit 2 of LR tells which stack was active
        "ite eq\n"
        "mrseq r0, msp\n"         // r0 = pointer to stack frame (MSP or PSP)
        "mrsne r0, psp\n"
        "b   supervisor_call_dispatch\n"
    );
}

// Cortex-M exception frame layout
typedef volatile struct {
    uint32_t r0;   // arg 1
    uint32_t r1;   // syscall number
    uint32_t r2;   // arg 2
    uint32_t r3;   // arg 3
    uint32_t r12;  // arg4
    uint32_t lr;
    uint32_t pc;   // where SVC was called from
    uint32_t psr;
} exception_stack_frame_t;

extern "C" void supervisor_call_dispatch(exception_stack_frame_t* frame) {
    // all calls use SVC #0, so we can use r1 to determine the syscall number
    uint8_t syscall_number = frame->r1;

    if (syscall_number >= (int) SYSCALL_MAX) {
        // Invalid syscall, set return value.
        frame->r0 = (uint32_t)(-1);
        return;
    }

    // From calling convention
    uint32_t arg1 = frame->r0;
    uint32_t arg2 = frame->r2;
    uint32_t arg3 = frame->r3;
    uint32_t arg4 = frame->r12;

    int ret = syscall_dispatch(syscall_number, arg1, arg2, arg3, arg4);

    // We modify frame->r0 here to return a value
    frame->r0 = ret;
}
