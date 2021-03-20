#ifndef SIMPLE_TIMERCOUNTER_ASYNC
#define SIMPLE_TIMERCOUNTER_ASYNC

#include "./TimerCounter_BaseClass.h"

typedef uint8_t byte;
typedef volatile byte reg;


class AsyncTimerCounter : public TimerCounter<byte>
{
protected:

public:
//Contructor
    AsyncTimerCounter(reg* TCNTn, reg* TCCRnA, reg* TCCRnB, reg* OCRnA, reg* OCRnB, reg* TIMSKn)
        : TimerCounter(TCNTn, TCCRnA, TCCRnB, OCRnA, OCRnB, TIMSKn){}

//ASSR
    void EnableAsync(bool external = false)
    {
        ASSR |= 0b00100000; //Set AS2

        if(external)
        {
            ASSR |= 0b01000000; //Set EXCLK
        }
    }
    void DisableAsync()
    {
        ASSR &= 0b10011111; //Clear AS2  & EXCLK
    }

    bool isBusy()
    {
        return ASSR & 0b0001000; //TCN2UB
    }

    bool OCRisBusy(char channel)
    {
        switch(channel)
        {
            case('A'):
                return ASSR & 0b00001000; //OCR2AUB
            case('B'):
                return ASSR & 0b00000100; //OCR2BUB
            default:
                return isBusy();
        }
    }

    bool CRAisBusy()
    {
        return ASSR & 0b00000010; //TCR2AUB
    }

    bool CRBisBusy()
    {
        return ASSR & 0b00000001; //TCR2BUB
    }    
};



#endif
