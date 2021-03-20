#include "avr-GPIO/GPIO.h"
#include "avr-simpleUSART/USART.h"
#include "avr-simpleTimerCounter/TimerCounter.h"
#include "multiSevSeg.h"
#include <util/delay.h>
#include <avr/interrupt.h>

GPIO sevSegPins[8] = 
{
    GPIO23,//A
    GPIO22,//B
    GPIO25,//C
    GPIO24,//D
    GPIO27,//E
    GPIO26,//F
    GPIO29,//G
    GPIO28 //DP
};
GPIO sevSegGND[4] =
{
    GPIO43,
    GPIO42,
    GPIO41,
    GPIO40
};
MultSevSeg disp = MultSevSeg(sevSegPins, sevSegGND, 4);

TIMER_OVF_ISR(1)
{
    GPIO13.Set();
}

TIMER_OVF_ISR(0)
{
    GPIO13.Set();
}



int main() 
{
    //Setup
    USART0.begin(9600);
    
    GPIO13.Output();
    
    GPIO13.Clear();
    _delay_ms(250);
    GPIO13.Set();
    _delay_ms(250);
    GPIO13.Clear();
    _delay_ms(250);
    
    //This works
        //TC0.SetCS(0b001); //(No Prescale) (See page 130 of docs)
        //TC0.EnableOverflowInterrupt();

    //This doesn't
        TC1.SetCS(0b001);
        TC1.EnableOverflowInterrupt();
    sei();
    
    
    while(1){};
    return 0;
}
