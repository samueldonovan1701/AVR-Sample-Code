#ifndef SIMPLE_TIMERCOUNTER
#define SIMPLE_TIMERCOUNTER
#include <avr/io.h>
#include <avr/interrupt.h>
#include "./TimerCounter_BaseClass.h"
#include "./AsyncTimerCounter.h"
#include "./TimerCounter_16.h"

typedef volatile unsigned char reg;
typedef unsigned char byte;


/////////////
//ISR Macros
/////////////
#define TIMER_CMP_ISR(N, CHANNEL) ISR(TIMER##N##_COMP##CHANNEL##_vect)
#define TIMER_OVF_ISR(N) ISR(TIMER##N##_OVF_vect)


//////////////////
//Timer Defintions
//////////////////

/* Timer Counter 0 (8-bit)
 *      Channel A Output (OC0A): PB7 (ATMEGA Pin 13) !!! "AND"ed with OC1C
 *      Channel B Output (OC0B): PG5 (ATMEGA Pin 4) 
 */
TimerCounter<> TC0 = TimerCounter<>(&TCNT0, &TCCR0A, &TCCR0B, &OCR0A, &OCR0B, &TIMSK0);

/* Timer Counter 1 (16-bit)
 *      Channel A Output (OC1A): PB5 (ATMEGA Pin 11)
 *      Channel B Output (OC1B): PB6 (ATMEGA Pin 12)
 *      Channel C Output (OC1C): PB7 (ATMEGA Pin 13) !!! "AND"ed with OC0A
 *      Input Capture    (ICP1): PD4 (ATMEGA Pin NA)
 */
TimerCounter_16 TC1 = TimerCounter_16(TCNT1L, TCNT1H, TCCR1A, TCCR1B, TCCR1C, OCR1AL, OCR1AH, OCR1BL, OCR1BH, OCR1CL, OCR1CH, TIMSK1);

/* Timer Counter 2 (8-bit Asynchrnous)
 *      Channel A Output (OC2A): PB4 (ATMEGA Pin 10)
 *      Channel B Output (OC2B): PH6 (ATMEGA Pin 9)
 */
AsyncTimerCounter TC2 = AsyncTimerCounter(&TCNT2, &TCCR2A, &TCCR2B, &OCR2A, &OCR2B, &TIMSK2);


/* Timer Counter 3 (36-bit)
 *      Channel A Output (OC3A): PE3 (ATMEGA Pin 5)
 *      Channel B Output (OC3B): PE4 (ATMEGA Pin 2)
 *      Channel C Output (OC3C): PE5 (ATMEGA Pin 3)
 *      Input Capture    (ICP3): PE7 (ATMEGA Pin NA)
 */
TimerCounter_16 TC3 = TimerCounter_16(TCNT3L, TCNT3H, TCCR3A, TCCR3B, TCCR3C, OCR3AL, OCR3AH, OCR3BL, OCR3BH, OCR3CL, OCR3CH, TIMSK3);


/* Timer Counter 4 (46-bit)
 *      Channel A Output (OC4A): PH3 (ATMEGA Pin 6)
 *      Channel B Output (OC4B): PH4 (ATMEGA Pin 7)
 *      Channel C Output (OC4C): PH5 (ATMEGA Pin 8)
 *      Input Capture    (ICP4): PL0 (ATMEGA Pin 49)
 */
TimerCounter_16 TC4 = TimerCounter_16(TCNT4L, TCNT4H, TCCR4A, TCCR4B, TCCR4C, OCR4AL, OCR4AH, OCR4BL, OCR4BH, OCR4CL, OCR4CH, TIMSK4);


/* Timer Counter 5 (56-bit)
 *      Channel A Output (OC5A): PL3 (ATMEGA Pin 46)
 *      Channel B Output (OC5B): PL4 (ATMEGA Pin 45)
 *      Channel C Output (OC5C): PL5 (ATMEGA Pin 44)
 *      Input Capture    (ICP5): PL1 (ATMEGA Pin 48)
 */
TimerCounter_16 TC5 = TimerCounter_16(TCNT5L, TCNT5H, TCCR5A, TCCR5B, TCCR5C, OCR5AL, OCR5AH, OCR5BL, OCR5BH, OCR5CL, OCR5CH, TIMSK5);


///////////////////////
//Static Util Functions
///////////////////////
class TimerCounters
{
    static void ResetAll()
    {
        //Reset & Hold all Prescaler Timers
        GTCCR |= 0b10000011; //Set TSM, PSRASY, and PSRSYNC

        //Reset Each Counter
        //TC0.Reset();
        //TC1.Reset();
        //TC2.Reset();
        //TC3.Reset();
        //TC4.Reset();
        //TC5.Reset();

        //Stop holding Prescale Timers
        GTCCR &= 0b01111111; //Clear TSM
    }

    void ResetAllExceptTC2()
    {
        //Reset & Hold all Synchrnous Prescale Timers
        GTCCR |= 0b10000001; //Set TSM, and PSRSYNC

        //Reset every Synchronous Counter
        //TC0.Reset();
        //TC1.Reset();
        //TC3.Reset();
        //TC4.Reset();
        //TC5.Reset();

        //Stop holding Prescale Timers
        GTCCR &= 0b01111111; //Clear TSM
    }
};

#endif
