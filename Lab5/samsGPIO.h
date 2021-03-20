#ifndef SAMS_GPIO
#define SAMS_GPIO

typedef unsigned char byte;
typedef volatile byte reg;

class GPIO
{
public:
    reg* DDR;
    reg* PORT_OUT;
    reg* PORT_IN;
    byte PIN;  
  
    GPIO();
    GPIO(reg* DDR, reg* PORT_OUT, reg* PORT_IN, byte PIN);

    
    #ifndef INPUT
    #define INPUT 0
    #endif
    #ifndef OUTPUT
    #define OUTPUT 1
    #endif
    void SetMode(byte mode);
    void Input();
    void Output();

    #ifndef LOW
    #define LOW 0
    #endif
    #ifndef HIGH
    #define HIGH 1
    #endif
    void SetState(byte STATE);
    void Set();
    void Clear();
    byte GetState();
};
#endif
