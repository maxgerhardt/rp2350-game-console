.syntax unified
.cpu cortex-m33
.thumb

.global start
.global main

/* Linker-provided symbols */
.extern _sidata    /* Start of .data init values in FLASH */
.extern _sdata     /* Start of .data in RAM */
.extern _edata     /* End of .data in RAM */
.extern _sbss      /* Start of .bss in RAM */
.extern _ebss      /* End of .bss in RAM */

/* Application start */
.type start, %function
start:
    push { lr } /* save link register to be used to jump back to the caller */

    /* Copy .data section from FLASH to RAM */
    ldr   r0, =_sidata
    ldr   r1, =_sdata
    ldr   r2, =_edata
1:
    cmp   r1, r2
    ittt  lo
    ldrlo r3, [r0], #4
    strlo r3, [r1], #4
    blo   1b

    /* Zero .bss section */
    ldr   r1, =_sbss
    ldr   r2, =_ebss
    movs  r3, #0
2:
    cmp   r1, r2
    itt   lo
    strlo r3, [r1], #4
    blo   2b

    /* call into libc constructors */
    bl    __libc_init_array

    /* Call main() */
    bl    main

    /* If main returns, let it return back to the caller. */
    /* TODO we have to figure out a proper way to handle this */
    pop  {pc} /* return to the caller */

.size start, . - start
