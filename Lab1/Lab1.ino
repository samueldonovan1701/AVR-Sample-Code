/*   Filename : Lab1.ino
 *   Author(s): Samuel Donovan
 *   Config: ATmega2560 @16MHz
 *   Description: 4-Bit binary counter, using Port B Pins 4-7. Although unoptimized, the code was written to be ledgible.
 */
#include <avr/io.h>
#include <util/delay.h>

void setPinMode(volatile unsigned char &DDR, unsigned char PIN, unsigned char MODE)
{
  if(MODE == 0)
    DDR &= ~(1 << PIN);
  else
    DDR |= 1 << PIN; 
}

void setPinState(volatile unsigned char &PORT, unsigned char PIN, unsigned char STATE)
{
  if(STATE == 0)
    PORT &= ~(1 << PIN);
  else
    PORT |= 1 << PIN; 
}

int main()
{  
  //Setup
  setPinMode(DDRB, 7, OUTPUT);
  setPinMode(DDRB, 6, OUTPUT);
  setPinMode(DDRB, 5, OUTPUT);
  setPinMode(DDRB, 4, OUTPUT);
  setPinState(PORTB, 7, 0);  
  setPinState(PORTB, 6, 0);  
  setPinState(PORTB, 5, 0);
  setPinState(PORTB, 4, 0);
  char n = B0000;

  
  while(true)
  {
    setPinState(PORTB, 7, ~((n >> 3) & 1));
    setPinState(PORTB, 6, ~((n >> 2) & 1));
    setPinState(PORTB, 5, ~((n >> 1) & 1));
    setPinState(PORTB, 4, ~(n&1));


    if(n == B1111)
      n = B0000;
    else
      n++;
    
    _delay_ms(1000);   
  }  
}
