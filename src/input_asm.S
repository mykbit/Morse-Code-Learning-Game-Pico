.syntax unified
.cpu    cortex-m0plus
.thumb
.global input_asm
.align 4


@ Entry point to the ASM portion of the program
input_asm:
    b       input_asm                                           @ Infinite loop


@ Set data alignment
.data
    .align 4
