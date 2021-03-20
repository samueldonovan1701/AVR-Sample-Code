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

#ifndef INPUT
#define INPUT 0
#endif
#ifndef OUTPUT
#define OUTPUT 1
#endif
//Functions
void GPIO_SetMode(GPIO &GPIO, byte MODE)
{
  if(MODE == INPUT)
    *GPIO.DDR &= ~(1 << GPIO.PIN);
  else
    *GPIO.DDR |= 1 << GPIO.PIN; 
}


#ifndef LOW
#define LOW 0
#endif
#ifndef HIGH
#define HIGH 1
#endif

void GPIO_SetState(GPIO &GPIO, byte STATE)
{
  if(STATE == LOW)
    *GPIO.PORT_OUT &= ~(1 << GPIO.PIN);
  else
    *GPIO.PORT_OUT |= 1 << GPIO.PIN;
}

byte GPIO_GetState(GPIO &GPIO)
{
  if(*GPIO.PORT_IN >> GPIO.PIN)
    return HIGH;
  else
    return LOW;
}
#endif
