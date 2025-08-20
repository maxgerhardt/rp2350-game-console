#ifndef _SYSCALL_DISPATCH_H_
#define _SYSCALL_DISPATCH_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

int syscall_dispatch(int svc_num, uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4);

#ifdef __cplusplus
}
#endif

#endif // _SYSCALL_DISPATCH_H_