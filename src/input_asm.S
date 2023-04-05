#include "hardware/regs/addressmap.h"
#include "hardware/regs/io_bank0.h"
#include "hardware/regs/timer.h"
#include "hardware/regs/m0plus.h"

.syntax unified
.cpu cortex-m0plus
.thumb
.global main_asm
.align 4

.equ DFLT_STATE_STRT, 1                             @ Specify the value to start flashing
.equ DFLT_STATE_STOP, 0                             @ Specify the value to stop flashing
.equ DFLT_ALARM_TIME, 3000000                       @ Specify the default alarm timeout

.equ GPIO_BTN_EN_MSK, 0x00400000                    @ Bit-22 for falling-edge event on GP21
.equ GPIO_BTN_EN_MSK_HIGH, 0x00800000               @ Bit-23 for rising-edge event on GP21

.equ GPIO_BTN_EN, 21                                @ Specify pin for the "enter" button
.equ GPIO_DIR_IN, 0                                 @ Specify input direction for a GPIO pin
.equ GPIO_ISR_OFFSET, 0x74                          @ GPIO is int #13 (vector table entry 29)
.equ ALRM_ISR_OFFSET, 0x40                          @ ALARM0 is int #0 (vector table entry16)
.equ WATCHDOG_LOAD_OFFSET, 0x04
.equ ENABLE_DISABLE_STATE, 0

.equ BUTTON_VARIABLE, 0
.equ PRESSED_COUNTER, 0
.equ SEQUNECE_DONE, 0

@ Entry point to the ASM portion of the program
main_asm:
 bl install_svc_isr             @ Install the alarm interrupt service routine
 bl install_gpio_isr            @ Install the gpio interrupt service routine

 movs r0, #0x1                  @ Bit[0]
 bl irq_enable_mask             @ Enable the alarm mask  

 bl gpio_irq_enable             @ enable the gpio interrupt
 ldr r0, =0x2000                @ Bit[13]
 bl irq_enable_mask             @ Enable the gpio mask

main_loop:
 
 ldr r1, =seqdone
 ldr r2, [r1]
 cmp r2, #1
 bne main_loop
 ldr r1, =bv
 ldr r0, [r1]
 
init_gpio_led:
push    {lr}
 movs    r0, #GPIO_BTN_EN
 bl      asm_gpio_init
 movs    r0, #GPIO_BTN_EN
 movs    r1, #GPIO_DIR_IN
 bl      asm_gpio_set_dir                  
pop     {pc}

install_svc_isr:
 ldr r2, =(PPB_BASE + M0PLUS_VTOR_OFFSET)       @ the address of the exceptions vector table
 ldr r1, [r2]                                   @ save the address
 movs r2, #ALRM_ISR_OFFSET                       @ get the offset for the particular interrrupt that we want
 add r2, r1                                     @ add it to the address of the vector table
 ldr r0, =svc_isr                               @ now direct that exception to the svc_isr function
 str r0, [r2]                                   @ now when that exception is called, the processor will go to svc_isr
 bx lr                                          @ branch to link register

install_gpio_isr:
 ldr r2, =(PPB_BASE + M0PLUS_VTOR_OFFSET)
 ldr r1, [r2]
 movs r2, #GPIO_ISR_OFFSET
 add r2, r1
 ldr r0, =gpio_isr
 str r0, [r2]
 bx lr

@ SVC interrupt service handler routine
.thumb_func @ Required for all interrupt service routines

// alaram interrut 
svc_isr:
 push {lr}                                      
 
@disable the interrupt 
 ldr r0, =(PPB_BASE + M0PLUS_NVIC_ICPR_OFFSET)
 movs r1, #0x1
 str r1, [r0]

@enable alarm 
 ldr r0, =(TIMER_BASE + TIMER_INTR_OFFSET)
 movs r1, #0x1
 str r1, [r0] 

 ldr r0, =seqdone
 ldr r1, [r0]
 mov r1, #1
 str r1, [r0]

svc_done:
 pop {pc}                                       

.thumb_func
gpio_isr:
 push {lr}

 ldr r0, =(IO_BANK0_BASE + IO_BANK0_PROC0_INTS2_OFFSET)
 str r1, [r0]

 ldr r0, =(IO_BANK0_BASE + IO_BANK0_INTR2_OFFSET)
 str r1, [r0]

 ldr r2, =GPIO_BTN_EN_MSK
 cmp r1, r2
 beq dot
 ldr r2, =GPIO_BTN_EN_MSK_HIGH
 cmp r1, r2
 beq dash

dot:
 ldr r0, =bv
 ldr r1, [r0]
 lsls r1, #1
 orr r1, #1
 str r1, [r0]
 ldr r0, =pcnt
 ldr r1, [r0]
 add r1, r1 #1
 str r1, [r0]
 bl done

dash:
 ldr r0, =bv
 ldr r1, [r0]
 lsls r1, #1
 orr r1, #0
 str r1, [r0]
 ldr r0, =pcnt
 ldr r1, [r0]
 add r1, r1 #1
 str r1, [r0]
 bl done

done:
 bl set_alarm
 
@enable the alarm interrupt 
 ldr r0, =(PPB_BASE + M0PLUS_NVIC_ICPR_OFFSET)
 movs r1, #0x1
 str r1, [r0]

 pop {pc}

set_alarm:
 push {lr}
 @set alarm
 ldr r0, =(TIMER_BASE + TIMER_TIMELR_OFFSET)
 ldr r0, [r0]
 ldr r1, =ltimer
 ldr r1, [r1]
 add r1, r1, r0
 ldr r0, =(TIMER_BASE + TIMER_ALARM0_OFFSET)
 str r1, [r0]

 pop {pc}

irq_enable_mask:
@ r0 = mask
 ldr r1, =(PPB_BASE + M0PLUS_NVIC_ICPR_OFFSET)
 str r0, [r1]
 ldr r1, =(PPB_BASE + M0PLUS_NVIC_ISER_OFFSET)
 str r0, [r1]
 bx lr

gpio_irq_enable:
 push {lr}
 movs r0, GPIO_BTN_EN
 bl asm_gpio_set_irq
 pop {pc}

.align 4
msg: .asciz "Hello World!\n"
.data

enable: .word ENABLE_DISABLE_STATE
lstate: .word DFLT_STATE_STRT
ltimer: .word DFLT_ALARM_TIME
bv: .int BUTTON_VARIABLE
pcnt: .int PRESSED_COUNTER
seqdone: .word SEQUNECE_DONE
