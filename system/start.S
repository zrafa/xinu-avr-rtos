#include <avr/io.h>

.macro vector name
    .weak \name
    .set \name, __vectors
    jmp \name
.endm
         
    .global _start
_start:

    .section .vectors
.global __vectors
__vectors:
    jmp RESET           ; Reset Handler
    vector __vector_1
    vector __vector_2
    vector __vector_3
    vector __vector_4
    vector __vector_5
    vector __vector_6
    vector __vector_7
    vector __vector_8
    vector __vector_9
    vector __vector_10
    vector __vector_11
    vector __vector_12
    vector __vector_13
    vector __vector_14
    vector __vector_15
    vector __vector_16
    vector __vector_17
    vector __vector_18
    vector __vector_19
    vector __vector_20
    vector __vector_21
    vector __vector_22
    vector __vector_23
    vector __vector_24
    vector __vector_25
#if lgt8f328p
    vector __vector_26
    vector __vector_27
    vector __vector_28
    vector __vector_29
#endif

    .set    __stack, RAMEND
    .text

RESET:
    clr     r1
    out     _SFR_IO_ADDR(SREG), r1
    ldi     r28,lo8(__stack)
    ldi     r29,hi8(__stack)
    out     _SFR_IO_ADDR(SPH), r29
    out     _SFR_IO_ADDR(SPL), r28

_do_copy_data:
    ldi     r17, hi8(__data_end)
    ldi     r26, lo8(__data_start)
    ldi     r27, hi8(__data_start)
    ldi     r30, lo8(__data_load_start)
    ldi     r31, hi8(__data_load_start)
    rjmp    2f
1:  lpm     r0, Z+
    st      X+, r0
2:  cpi     r26, lo8(__data_end)
    cpc     r27, r17
    brne    1b

_do_clear_bss:
    ldi     r17, hi8(__bss_end)
    ldi     r26, lo8(__bss_start)
    ldi     r27, hi8(__bss_start)
    rjmp    4f
3:  st      X+, r1
4:  cpi     r26, lo8(__bss_end)
    cpc     r27, r17
    brne    3b

    jmp     nulluser

