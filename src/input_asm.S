#include "hardware/regs/addressmap.h"
#include "hardware/regs/io_bank0.h"
#include "hardware/regs/timer.h"
#include "hardware/regs/m0plus.h"

.syntax unified
.cpu    cortex-m0plus
.thumb
.global input_asm
.align  4

.equ    GPIO_DIR_IN,            0               @ Specify input direction for a GPIO pin
.equ    GPIO_DIR_OUT,           1               @ Specify output direction for a GPIO pin

.equ    GP21,                   21              @ Specify pin for the GP21 button
.equ    GP21_EDGE_FALL_MASK,    0x00400000      @ GP21 edge fall mask
.equ    GP21_EDGE_RISE_MASK,    0x00800000      @ GP21 edge rise mask

.equ    GPIO_ISR_OFFSET,        0x74            @ GPIO is int #13 (vector table entry 29)
.equ    ALARM0_ISR_OFFSET,      0x40            @ ALARM0 is int #0 (vector table entry 16)

.equ    ALARM0_DELAY,           1000000         @ Alarm delay

.equ    DOT,                    0               @ "." in morse_buffer
.equ    DASH,                   1               @ "-" in morse_buffer

.equ    MORSE_BUFFER_DFLT,      1               @ Default morse_buffer value
.equ    EDGE_FALL_TIME_DFLT,    1               @ Default edge_fall_time value
.equ    IS_INPUT_DONE_DFLT,     0               @ Default edge_fall_time value


/*
 * Entrypoint to the ASM program
 */
input_asm:
    push    {lr}
    bl      init_gp21
    bl      install_gpio_isr
    bl      install_alarm_isr
input_asm_reset_data:
    ldr     r0, =MORSE_BUFFER_DFLT
    ldr     r1, =morse_buffer
    str     r0, [r1]
    ldr     r0, =EDGE_FALL_TIME_DFLT
    ldr     r1, =edge_fall_time
    str     r0, [r1]
    ldr     r0, =IS_INPUT_DONE_DFLT
    ldr     r1, =is_input_done
    str     r0, [r1]
input_asm_loop:
    ldr     r1, =is_input_done
    ldr     r0, [r1]
    cmp     r0, #1
    beq     input_asm_done
    b       input_asm_loop
input_asm_done:
    bl      remove_gpio_isr
    bl      cancel_alarm_isr
    bl      remove_alarm_isr
    ldr     r1, =morse_buffer
    ldr     r0, [r1]
    pop     {pc}


/*
 * ------------------------ gpio_isr -------------------------
 */

/*
 * Initialize gp21
 */
init_gp21:
    push    {lr}
    movs    r0, #GP21
    bl      asm_gpio_init
    movs    r0, #GP21
    movs    r1, #GPIO_DIR_IN
    bl      asm_gpio_set_dir
    movs    r0, #GP21
    bl      asm_gpio_set_irq_edge_fall
    movs    r0, #GP21
    bl      asm_gpio_set_irq_edge_rise
    pop     {pc}

/*
 * Install gpio_isr
 */
install_gpio_isr:
    @ Set gpio_isr to GPIO_ISR_OFFSET in the vector table
    ldr     r2, =(PPB_BASE + M0PLUS_VTOR_OFFSET)
    ldr     r1, [r2]
    ldr     r0, =gpio_isr
    str     r0, [r1, #GPIO_ISR_OFFSET]
    @ Enable GPIO interrupt clearing in NVIC_ICPR register
    ldr     r0, =(PPB_BASE + M0PLUS_NVIC_ICPR_OFFSET)
    movs    r1, #1
    lsls    r1, #13
    str     r1, [r0]
    @ Enable GPIO interrupt in NVIC_ISER register
    ldr     r0, =(PPB_BASE + M0PLUS_NVIC_ISER_OFFSET)
    movs    r1, #1
    lsls    r1, #13
    str     r1, [r0]
    bx      lr

/*
 * Remove gpio_isr
 */
remove_gpio_isr:
    @ Enable GPIO interrupt clearing in NVIC_ICPR register
    ldr     r0, =(PPB_BASE + M0PLUS_NVIC_ICPR_OFFSET)
    movs    r1, #0
    lsls    r1, #13
    str     r1, [r0]
    @ Enable GPIO interrupt in NVIC_ISER register
    ldr     r0, =(PPB_BASE + M0PLUS_NVIC_ISER_OFFSET)
    movs    r1, #0
    lsls    r1, #13
    str     r1, [r0]
    bx      lr

/*
 * GPIO interrupt service handler
 */
.thumb_func
gpio_isr:
    push    {lr}
    @ Load IO_BANK0 INTR2 register value to r1 (gp16-gp23)
    ldr     r0, =(IO_BANK0_BASE + IO_BANK0_PROC0_INTS2_OFFSET)      
    ldr     r1, [r0]
    @ Detect fall/rise edge
    ldr     r2, =#GP21_EDGE_FALL_MASK
    cmp     r1, r2
    beq     gpio_isr_edge_fall
    ldr     r2, =#GP21_EDGE_RISE_MASK
    cmp     r1, r2
    beq     gpio_isr_edge_rise
    b       gpio_isr_done
gpio_isr_edge_fall:
    @ Cancel exit alarm
    bl      cancel_alarm_isr
    @ Save edge fall timestamp
    bl      asm_time_ms
    movs    r1, r0
    ldr     r1, =edge_fall_time
    str     r0, [r1]
    b       gpio_isr_done
gpio_isr_edge_rise:
    @ Schedule exit alarm
    bl      schedule_alarm_isr
    @ Calculate delta between edge fall timestamp and edge rise timestamp
    @ if (delta < 1000) gpio_isr_dot;
    @ else              gpio_isr_dash;
    bl      asm_time_ms
    ldr     r2, =edge_fall_time
    ldr     r1, [r2]
    subs    r0, r1
    ldr     r1, =1000
    cmp     r0, r1
    blt     gpio_isr_dot
    b       gpio_isr_dash
gpio_isr_dot:
    @ Put 0 in the buffer
    ldr     r2, =morse_buffer
    ldr     r0, [r2]
    lsls    r0, #1
    movs    r1, #DOT
    orrs    r0, r1
    str     r0, [r2]
    b       gpio_isr_done
gpio_isr_dash:
    @ Put 1 in the buffer
    ldr     r2, =morse_buffer
    ldr     r0, [r2]
    lsls    r0, #1
    movs    r1, #DASH
    orrs    r0, r1
    str     r0, [r2]
    b       gpio_isr_done
gpio_isr_done:
    @ Clear interrupt for gp21
    ldr     r0, =(IO_BANK0_BASE + IO_BANK0_INTR2_OFFSET)
    ldr     r1, =#0xf
    lsls    r1, #20
    str     r1, [r0]
    pop     {pc}


/*
 * ------------------------ alarm_isr ------------------------
 */

/*
 * Install alarm_isr
 */
install_alarm_isr:
    @ Set alarm_isr to ALARM0_ISR_OFFSET in the vector table
    ldr     r2, =(PPB_BASE + M0PLUS_VTOR_OFFSET)
    ldr     r1, [r2]
    ldr     r0, =alarm_isr
    str     r0, [r1, #ALARM0_ISR_OFFSET]
    @ Enable ALARM0 interrupt clearing in NVIC_ICPR register
    ldr     r0, =(PPB_BASE + M0PLUS_NVIC_ICPR_OFFSET)
    movs    r1, #1
    str     r1, [r0]
    @ Enable ALARM0 interrupt in NVIC_ISER register
    ldr     r0, =(PPB_BASE + M0PLUS_NVIC_ISER_OFFSET)
    movs    r1, #1
    str     r1, [r0]
    bx      lr

/*
 * Schedule alarm_isr
 */
schedule_alarm_isr:
    @ Enable ALARM0 interrupt
    ldr     r1, =(TIMER_BASE + TIMER_INTE_OFFSET)
    ldr     r2, [r1]
    movs    r3, #1
    lsls    r3, #TIMER_INTE_ALARM_0_LSB
    orrs    r2, r3
    str     r2, [r1]
    @ Set TIMER_ALARM0 register value to TIMER_TIMELR + r0
    ldr     r0, =ALARM0_DELAY
    ldr     r1, =(TIMER_BASE + TIMER_TIMELR_OFFSET)
    ldr     r2, [r1]
    add     r2, r0
    ldr     r1, =(TIMER_BASE + TIMER_ALARM0_OFFSET)
    str     r2, [r1]
    bx      lr

/*
 * Cancel alarm_isr
 */
cancel_alarm_isr:
    @ Disable ALARM0 interrupt
    ldr     r0, =(TIMER_BASE + TIMER_INTE_OFFSET)
    ldr     r1, [r0]
    movs    r2, #1
    lsls    r2, #TIMER_INTE_ALARM_0_LSB
    bics    r1, r2
    str     r1, [r0]
    @ Set TIMER_ALARM0 value to TIMER_TIMELR value + 0
    ldr     r1, =(TIMER_BASE + TIMER_TIMELR_OFFSET)
    ldr     r2, [r1]
    ldr     r1, =(TIMER_BASE + TIMER_ALARM0_OFFSET)
    str     r2, [r1]
    @ Clear interrupt
    ldr     r0, =(TIMER_BASE + TIMER_INTR_OFFSET)
    movs    r1, #1
    str     r1, [r0]
    bx      lr

/*
 * Remove alarm_isr
 */
remove_alarm_isr:
    @ Enable ALARM0 interrupt clearing in NVIC_ICPR register
    ldr     r0, =(PPB_BASE + M0PLUS_NVIC_ICPR_OFFSET)
    movs    r1, #0
    str     r1, [r0]
    @ Enable ALARM0 interrupt in NVIC_ISER register
    ldr     r0, =(PPB_BASE + M0PLUS_NVIC_ISER_OFFSET)
    movs    r1, #0
    str     r1, [r0]
    bx      lr

/*
 * Alarm interrupt service handler
 */
.thumb_func
alarm_isr:
    push    {lr}
    @ Set is_input_done as true
    movs    r0, #1
    ldr     r1, =is_input_done
    str     r0, [r1]
    @ Clear interrupt
    ldr     r0, =(TIMER_BASE + TIMER_INTR_OFFSET)
    movs    r1, #1
    str     r1, [r0]
    pop     {pc}


.align 4
dot:       .asciz ".\n"
dash:      .asciz "-\n"

.data
morse_buffer:   .word MORSE_BUFFER_DFLT
edge_fall_time: .word EDGE_FALL_TIME_DFLT
is_input_done:  .word IS_INPUT_DONE_DFLT
