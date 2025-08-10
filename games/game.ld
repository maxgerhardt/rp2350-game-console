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
    } > FLASH

    /* Initialized data section */
    .data :
    {
        _sdata = .;
        *(.data*)
        _edata = .;
    } > RAM
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
    ._user_stack :
    {
        . = ALIGN(8);
        _estack = ORIGIN(RAM) + LENGTH(RAM);
    } > RAM

    /* Symbols for heap/stack management */
    _end = .;
}
