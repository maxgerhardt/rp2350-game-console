#include <Arduino.h>
#include "svc_handler.h"

static syscall_t syscall_table[] = {
    syscall_print,
    syscall_exit,
    // more...
};
#define NUM_SYSCALLS (sizeof(syscall_table) / sizeof(syscall_t))
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
typedef struct {
    uint32_t r0;   // arg
    uint32_t r1;
    uint32_t r2;
    uint32_t r3;
    uint32_t r12;
    uint32_t lr;
    uint32_t pc;   // where SVC was called from
    uint32_t psr;
} exception_stack_frame_t;

extern "C" void supervisor_call_dispatch(exception_stack_frame_t* frame) {
    // all calls use SVC #0, so we can use r1 to determine the syscall number
    uint8_t svc_number = frame->r1;

    if (svc_number >= NUM_SYSCALLS) {
        // Invalid syscall
        frame->r0 = (uint32_t)(-1);
        return;
    }

    void* arg = (void*)frame->r0;
    int ret = syscall_table[svc_number](arg);

    // You can modify frame->r0 here to return a value
    frame->r0 = ret; // return 0 to app
}
