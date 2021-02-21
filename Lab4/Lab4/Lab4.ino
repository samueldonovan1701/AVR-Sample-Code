//#include "samsSerial.h"
#include "sams8x8Display.h"
#include <avr/io.h>
#include <util/delay.h>


LED_Display led = 
{
    .DIN = {.DDR=&DDRH, .PORT_OUT=&PORTH, .PORT_IN=&PINH, .PIN=5}, //Pin 8
    .CS = {.DDR=&DDRH, .PORT_OUT=&PORTH, .PORT_IN=&PINH, .PIN=6},  //Pin 9
    .CLK = {.DDR=&DDRB, .PORT_OUT=&PORTB, .PORT_IN=&PINB, .PIN=4} //Pin 10   
};

int main()
{    
    SetupLEDGPIO(led);
    TurnOnLED(led);
    ClearLED(led);
    SetScanLimitLED(led, 8);

    char temp = '0';

    //WriteChar(led, 0);
    /*while(1)
    {
      for(temp = '0'; temp < 58; temp++)
      {
        WriteChar(led, temp);
        _delay_ms(1000);
      }
      for(temp = 'A'; temp < 91; temp++)
      {
        WriteChar(led, temp);
        _delay_ms(1000);
      }
    }*/
    while(1){};
}
