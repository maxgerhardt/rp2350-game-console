/* Application linker script for Cortex-M */

ENTRY(start)

MEMORY
{
    /* 16MB total flash at 0x10000000, app starts 1MB into it */
    FLASH (rx)  : ORIGIN = 0x10000000 + 0x00100000, LENGTH = (16M - 1M)
    /* 512KB total RAM at 0x20000000, app uses upper 256KB */
    RAM   (rwx) : ORIGIN = 0x20000000 + 256K, LENGTH = 256K
}

SECTIONS
{
    /* Reserve space for application header */
    .app_header :
    {
        /* 48 bytes for app_header_t struct */
        . = ALIGN(4);
        KEEP(*(.app_header))  /* Allow C code to define it explicitly if needed */
        . += 48;
    } > FLASH

    .text :
    {
        *(.text*)                /* Program code */
        *(.rodata*)              /* Read-only data */
        KEEP(*(.init))
        KEEP(*(.fini))
        /* Pull all c'tors into .text */
        *crtbegin.o(.ctors)
        *crtbegin?.o(.ctors)
        *(EXCLUDE_FILE(*crtend?.o *crtend.o) .ctors)
        *(SORT(.ctors.*))
        *(.ctors)
        /* Followed by destructors */
        *crtbegin.o(.dtors)
        *crtbegin?.o(.dtors)
        *(EXCLUDE_FILE(*crtend?.o *crtend.o) .dtors)
        *(SORT(.dtors.*))
        *(.dtors)
        . = ALIGN(4);
        /* preinit data */
        PROVIDE_HIDDEN (__preinit_array_start = .);
        KEEP(*(SORT(.preinit_array.*)))
        KEEP(*(.preinit_array))
        PROVIDE_HIDDEN (__preinit_array_end = .);
        . = ALIGN(4);
        /* init data */
        PROVIDE_HIDDEN (__init_array_start = .);
        KEEP(*(SORT(.init_array.*)))
        KEEP(*(.init_array))
        PROVIDE_HIDDEN (__init_array_end = .);

        . = ALIGN(4);
        /* finit data */
        PROVIDE_HIDDEN (__fini_array_start = .);
        *(SORT(.fini_array.*))
        *(.fini_array)
        PROVIDE_HIDDEN (__fini_array_end = .);

        *(.eh_frame*)
        . = ALIGN(4);
    } > FLASH

    /* Initialized data section */
    .data :
    {
        _sdata = .;
        *(.data*)
        _edata = .;
    } > RAM AT > FLASH
    _sidata = LOADADDR(.data);


    /* Zero-initialized data section */
    .bss (NOLOAD):
    {
        _sbss = .;
        *(.bss*)
        *(COMMON)
        _ebss = .;
    } > RAM

    /* Stack at top of RAM */
    ._user_heap_stack (NOLOAD):
    {
        __end__ = .;
        end = __end__;
        . = ORIGIN(RAM) + LENGTH(RAM);
        _estack = .;
        __HeapLimit = .;
    } > RAM

    /* Symbols for heap/stack management */
    _end = .;
}
