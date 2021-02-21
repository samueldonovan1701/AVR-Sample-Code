#ifndef SAMS_GPIO
#define SAMS_GPIO
typedef volatile unsigned char reg;

struct GPIO 
{
  reg* DDR;
  reg* PORT_OUT;
  reg* PORT_IN;
  byte PIN;  
};

//Functions
void SetMode(GPIO &GPIO, byte MODE)
{
  if(MODE == INPUT)
    *GPIO.DDR &= ~(1 << GPIO.PIN);
  else
    *GPIO.DDR |= 1 << GPIO.PIN; 
}

void SetState(GPIO &GPIO, byte STATE)
{
  if(STATE == LOW)
    *GPIO.PORT_OUT &= ~(1 << GPIO.PIN);
  else
    *GPIO.PORT_OUT |= 1 << GPIO.PIN;
}

byte GetState(GPIO &GPIO)
{
  if(*GPIO.PORT_IN >> GPIO.PIN)
    return HIGH;
  else
    return LOW;
}
#endif