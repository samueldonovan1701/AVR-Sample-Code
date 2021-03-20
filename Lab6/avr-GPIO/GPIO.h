#ifndef AVR_GPIO
#define AVR_GPIO
#include <avr/io.h>

typedef uint8_t byte;
typedef volatile uint8_t reg;

class GPIO
{
private:
	reg* DDR;
    reg* PORT_OUT;
    reg* PORT_IN;
    byte PIN;  


public:
    GPIO(reg* DDR, reg* PORT_OUT, reg* PORT_IN, byte PIN)
    {
		this->DDR = DDR;
		this->PORT_OUT = PORT_OUT;
		this->PORT_IN = PORT_IN;
		this->PIN = PIN;
	};
    #define GPIO(X,P) GPIO(&DDR##X, &PORT##X, &PORT##X, P)

    
    #ifndef INPUT
    #define INPUT 0
    #endif
    #ifndef OUTPUT
    #define OUTPUT 1
    #endif
    void SetMode(byte mode)
    {
		if(mode == INPUT)
			Input();
		else
			Output();
	};
    void Input()
    {
    	*DDR &= ~(1 << PIN);
	}
    void Output()
	{
    	*DDR |= 1 << this->PIN; 
	}

    #ifndef LOW
    #define LOW 0
    #endif
    #ifndef HIGH
    #define HIGH 1
    #endif
    void Write(byte state)
    {
  		if(state == LOW)
    		this->Set();
  		else
    		this->Clear();
	}
    void Set()
    {
  		*PORT_OUT |= 1 << PIN;
	}
    void Clear()
	{
		*PORT_OUT &= ~(1 << PIN);
	}
    void Toggle()
    {
        *PORT_OUT ^= (1 << PIN);
    }

    byte Read()
	{
		return (*PORT_IN >> PIN) & 1;
	}
    bool isHigh()
    {
        return this->Read();
    }
    bool isLow()
    {
        return !isHigh();
    }
};

    #if defined(ARDUINO_AVR_MEGA2560)
        #include "./pins/mega2560.h"
    #else
        #warning "arduino-gpio: Board unsupported"
    #endif

#endif
