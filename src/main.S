.syntax unified                                                 @ Specify unified assembly syntax
.cpu    cortex-m0plus                                           @ Specify CPU type is Cortex M0+
.thumb                                                          @ Specify thumb assembly for RP2040
.global main_asm                                                @ Provide program starting address to the linker
.align 4                                                        @ Specify code alignment


@ Entry point to the ASM portion of the program
main_asm:
    b       main_asm                                           @ Infinite loop


@ Set data alignment
.data
    .align 4
