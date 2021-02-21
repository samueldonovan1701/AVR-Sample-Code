#define __SFR_OFFSET 0 //Something to do with register address offsetting

#include "avr/io.h"

.global start
.global count

delay_n_ms: //For 16 MHz
    ldi     r31, 3000>>8
    ldi     r30, 3000&255
delay_lp:
    sbiw    r30, 1
    brne    delay_lp
    subi    r20, 1
    brne    delay_n_ms
    ret

start:
    sbi     DDRB,7 
    sbi     DDRB,6
    sbi     DDRB,5
    sbi     DDRB,4
    ldi     r16, 0b11110000 //Logic is inverted, so we're counting down
    ret

count: //NOTE: r16 value auto-loops thanks to integer overflow
    out     PORTB, r16  //Write r16 to PORTB
    
    //Delay
    ldi     r20, 250    //Max delay == 255
    call    delay_n_ms

    subi     r16, 0b00010000 //We decrement by "0.5" to increase percieved delay to 0.5
    jmp     count //Loop
