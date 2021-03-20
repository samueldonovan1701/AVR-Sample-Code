#include "samsGPIO.h"

GPIO::GPIO()
{
    this->DDR = nullptr;
    this->PORT_OUT = nullptr;
    this->PORT_IN = nullptr;
    this->PIN = 0;
}

GPIO::GPIO(reg* DDR, reg* PORT_OUT, reg* PORT_IN, byte PIN)
{
    this->DDR = DDR;
    this->PORT_OUT = PORT_OUT;
    this->PORT_IN = PORT_IN;
    this->PIN = PIN;
}

void GPIO::SetMode(byte mode)
{
  if(mode == INPUT)
    Input();
  else
    Output();
}

void GPIO::Input()
{
    *DDR &= ~(1 << PIN);
}

void GPIO::Output()
{
    *DDR |= 1 << this->PIN; 
}

void GPIO::SetState(byte state)
{
  if(state == LOW)
    this->Clear();
  else
    this->Set();
}

void GPIO::Set()
{
  *PORT_OUT |= 1 << PIN;
}

void GPIO::Clear()
{
  *PORT_OUT &= ~(1 << PIN);
}

byte GPIO::GetState()
{
  return (*PORT_IN >> PIN) & 1;
}
