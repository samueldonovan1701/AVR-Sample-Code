/*   Filename : Lab2.ino
 *   Author(s): Samuel Donovan
 *   Config: ATmega2560 @16MHz
 *   Description: 
 */
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
typedef volatile unsigned char gpioreg;

struct GPIO_Pin 
{
  gpioreg* ddr;
  gpioreg* write;
  gpioreg* read;
  byte pin;  
};
struct SegDisplay
{
  GPIO_Pin A;
  GPIO_Pin B;
  GPIO_Pin C;
  GPIO_Pin D;
  GPIO_Pin E;
  GPIO_Pin F;
  GPIO_Pin G;
  GPIO_Pin DP;  
};

//Pin Functions
void setPinMode(GPIO_Pin PIN, byte MODE)
{
  if(MODE == INPUT)
    *PIN.ddr &= ~(1 << PIN.pin);
  else
    *PIN.ddr |= 1 << PIN.pin; 
}
void setPinState(GPIO_Pin PIN, byte STATE)
{
  if(STATE == LOW)
    *PIN.write &= ~(1 << PIN.pin);
  else
    *PIN.write |= 1 << PIN.pin; 
}
byte getPinState(GPIO_Pin PIN)
{
  if(*PIN.read >> PIN.pin)
    return HIGH;
  else
    return LOW;
}

//Seg Display Functions
void setupSegDisplay(SegDisplay disp)
{
  setPinMode(disp.A, OUTPUT);
  setPinMode(disp.B, OUTPUT);
  setPinMode(disp.C, OUTPUT);
  setPinMode(disp.D, OUTPUT);
  setPinMode(disp.E, OUTPUT);
  setPinMode(disp.F, OUTPUT);
  setPinMode(disp.G, OUTPUT);
  setPinMode(disp.DP, OUTPUT);
}
void showSegDisplay(byte b, SegDisplay disp, bool dp=false)
{
  if(dp)
    setPinState(disp.DP, HIGH);
  else
    setPinState(disp.DP, LOW);
    
  switch(b)
  {
    case 0x0:
      setPinState(disp.A, HIGH);
      setPinState(disp.B, HIGH);
      setPinState(disp.C, HIGH);
      setPinState(disp.D, HIGH);
      setPinState(disp.E, HIGH);
      setPinState(disp.F, HIGH);
      setPinState(disp.G, LOW);
      break;
    case 0x1:
      setPinState(disp.A, LOW);
      setPinState(disp.B, HIGH);
      setPinState(disp.C, HIGH);
      setPinState(disp.D, LOW);
      setPinState(disp.E, LOW);
      setPinState(disp.F, LOW);
      setPinState(disp.G, LOW);
      break;
    case 0x2:
      setPinState(disp.A, HIGH);
      setPinState(disp.B, HIGH);
      setPinState(disp.C, LOW);
      setPinState(disp.D, HIGH);
      setPinState(disp.E, HIGH);
      setPinState(disp.F, LOW);
      setPinState(disp.G, HIGH);
      break;
    case 0x3:
      setPinState(disp.A, HIGH);
      setPinState(disp.B, HIGH);
      setPinState(disp.C, HIGH);
      setPinState(disp.D, HIGH);
      setPinState(disp.E, LOW);
      setPinState(disp.F, LOW);
      setPinState(disp.G, HIGH);
      break;
    case 0x4:
      setPinState(disp.A, LOW);
      setPinState(disp.B, HIGH);
      setPinState(disp.C, HIGH);
      setPinState(disp.D, LOW);
      setPinState(disp.E, LOW);
      setPinState(disp.F, HIGH);
      setPinState(disp.G, HIGH);
      break;
    case 0x5:
      setPinState(disp.A, HIGH);
      setPinState(disp.B, LOW);
      setPinState(disp.C, HIGH);
      setPinState(disp.D, HIGH);
      setPinState(disp.E, LOW);
      setPinState(disp.F, HIGH);
      setPinState(disp.G, HIGH);
      break;
    case 0x6:
      setPinState(disp.A, LOW);
      setPinState(disp.B, LOW);
      setPinState(disp.C, HIGH);
      setPinState(disp.D, HIGH);
      setPinState(disp.E, HIGH);
      setPinState(disp.F, HIGH);
      setPinState(disp.G, HIGH);
      break;
    case 0x7:
      setPinState(disp.A, HIGH);
      setPinState(disp.B, HIGH);
      setPinState(disp.C, HIGH);
      setPinState(disp.D, LOW);
      setPinState(disp.E, LOW);
      setPinState(disp.F, LOW);
      setPinState(disp.G, LOW);
      break;
    case 0x8:
      setPinState(disp.A, HIGH);
      setPinState(disp.B, HIGH);
      setPinState(disp.C, HIGH);
      setPinState(disp.D, HIGH);
      setPinState(disp.E, HIGH);
      setPinState(disp.F, HIGH);
      setPinState(disp.G, HIGH);
      break;
    case 0x9:
      setPinState(disp.A, HIGH);
      setPinState(disp.B, HIGH);
      setPinState(disp.C, HIGH);
      setPinState(disp.D, LOW);
      setPinState(disp.E, LOW);
      setPinState(disp.F, HIGH);
      setPinState(disp.G, HIGH);
      break;
    default:
      setPinState(disp.A, LOW);
      setPinState(disp.B, LOW);
      setPinState(disp.C, LOW);
      setPinState(disp.D, LOW);
      setPinState(disp.E, LOW);
      setPinState(disp.F, LOW);
      setPinState(disp.G, LOW);
      break;    
  }
}

int main()
{
  // Vars
  SegDisplay disp = 
  {
    A: {&DDRB, &PORTB, NULL, 7},
    B: {&DDRB, &PORTB, NULL, 6},
    C: {&DDRB, &PORTB, NULL, 5},
    D: {&DDRB, &PORTB, NULL, 4},
    E: {&DDRH, &PORTH, NULL, 6},
    F: {&DDRH, &PORTH, NULL, 5},
    G: {&DDRH, &PORTH, NULL, 4},
    DP:{NULL, NULL, NULL, NULL}
  };
  GPIO_Pin snsr = {&DDRE, NULL, &PINE, 3};
  byte n = 0;
  byte prevState = LOW;

  //Setup
  setupSegDisplay(disp);
  setPinMode(snsr, INPUT);
  showSegDisplay(n, disp);  

  //Loop
  while(1)
  {
    if(getPinState(snsr) == HIGH)
    {
      if(prevState == LOW)
      {
        n++;
        if(n > 9)
          n = 0;
          
        showSegDisplay(n, disp);
      }
      prevState = HIGH;
    }
    else
    {
      prevState = LOW;
    }
  }
}
