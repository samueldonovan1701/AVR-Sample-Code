#ifndef SIMPLE_TIMERCOUNTER_8
#define SIMPLE_TIMERCOUNTER_8

typedef uint8_t byte;
typedef volatile byte reg;

template <typename TCSize = byte> class TimerCounter
{
protected:
//Registers
	reg* TCNTn; //Timer Value

	reg* TCCRnA; //Control Register A
	reg* TCCRnB; //Control Register B

	reg* OCRnA; //Output Compare Register A
	reg* OCRnB; //Output Compare Register B

	reg* TIMSKn; //Interrupt Mask Register

public:
//Contructor
	TimerCounter(reg* TCNTn, reg* TCCRnA, reg* TCCRnB, reg* OCRnA, reg* OCRnB, reg* TIMSKn)
	{
		this->TCNTn = TCNTn;

		this->TCCRnA = TCCRnA;
		this->TCCRnB = TCCRnB;


		this->OCRnA = OCRnA;
		this->OCRnB = OCRnB;

		this->TIMSKn = TIMSKn;
	}

//TCNTn
    virtual void SetVal(TCSize val)
    {
        *TCNTn = val;
    }
    virtual TCSize GetVal()
    {
        return *TCNTn;
    }

//TCCRnA
	virtual void SetCOM(byte mask, char channel = 'A') //Set Compare Output Match
	{
		mask &= 0b11; //Truncate

        switch(channel)
        {
            case 'A':  //COMnA 1:0 | TCCRnA 7:6
                *TCCRnA &= 0b00111111;  //Clear
                *TCCRnA |= (mask << 6);    //Set
                return;
            case 'B':  //COMnB 1:0 | TCCRnA 5:4
                *TCCRnA &= 0b11001111;  //Clear
                *TCCRnA |= (mask << 4);    //Set
                return;
            default:
                return;    
        }
	}
    virtual byte GetCOM(char channel = 'A')
    {
        byte mask;
        switch(channel)
        {
            case 'A':  //COMnA 1:0 | TCCRnA 7:6
                mask = (*TCCRnA >> 6 ) & 0b11;
                break;
            case 'B':  //COMnB 1:0 | TCCRnA 5:4
                mask = (*TCCRnA >> 4 ) & 0b11;
                break;
            default:
                mask =  -1;    
        };

        return mask;
    }

    virtual void SetWGM(byte mask) //Set Wave Generation Mode
    {
        mask &= 0b111; //Truncate
        
        //WGMn 1:0 | TCCRnA 1:0
        *TCCRnA &= 0b11111100;  //Clear
        *TCCRnA |= (mask & 0b011); //Set

        //WGM 2 | TCCRnB 4
        *TCCRnB &= 0b11110111;  //Clear
        *TCCRnB |= ((mask & 0b100) << 1); // Set
    }
    virtual byte GetWGM()
    {
        byte mask;

        //WGMn 1:0 | TCCRnA 1:0
        mask = *TCCRnA & 0b011;

        //WGM 2 | TCCRnB 4
        mask |= (*TCCRnB >> 1) & 0b100; 

        return mask;
    }

//TCCRnB
    virtual void ForceOutput(char channel = 'A') //Note: will not clear the timer or trigger an interrupt
    {
        
        switch(channel)
        {
            case('A'): //FOCnA | TCCRnB 7
                *TCCRnB |= 0b10000000;
                return;
            case('B'): //FOCnB | TCCRnB 6
                *TCCRnB |= 0b01000000;
                return;
            default:
                return;
        }
    }

    virtual void SetCS(byte mask) //Set Clock Select
    {
        //Cast & Truncate
        mask &= 0b111;

        //CSn 2:0 | TCCRnB 2:0
        *TCCRnB &= 0b11111000; //Clear
        *TCCRnB |= mask; //Set
    }
    virtual byte GetCS()
    {
        //CSn 2:0 | TCCRnB 2:0
        return *TCCRnB & 0b111;
    }

//OCRnx
    virtual void SetOCR(TCSize val, char channel = 'A') //Set Output Compare Register
    {
        switch(channel)
        {
            case('A'):
                *OCRnA = val;
                return;
            case('B'):
                *OCRnB = val;
                return;
            default:
                return;
        }
    }
    virtual TCSize GetOCR(char channel='A')
    {
        switch(channel)
        {
            case('A'):
                return *OCRnA;
            case('B'):
                return *OCRnB;
            default:
                return -1;
        }
    }

//TIMSKn
    virtual void EnableInterrupt(char channel = 'A')
    {
        switch(channel)
        {
            case('A'):
                //OCIEnA | TIMSKn 1
                *TIMSKn |= 0b00000010; //Set
                return;
            case('B'):
                //OCIEnB | TIMSKn 2
                *TIMSKn |= 0b00000100; //Set
                return;
            default:
                return;
        }
    }
    virtual void DisableInterrupt(char channel = 'A')
    {
        switch(channel)
        {
            case('A'):
                //OCIEnA | TIMSKn 1
                *TIMSKn &= 0b11111101; //Clear
                return;
            case('B'):
                //OCIEnB | TIMSKn 2
                *TIMSKn &= 0b11111011; //Clear
                return;
            default:
                return;
        }
    }

    virtual void EnableOverflowInterrupt()
    {
        //OIEn | TIMSKn 0
        *TIMSKn |= 0b00000001; //Set
    }
    virtual void DisableOverflowInterrupt()
    {
        *TIMSKn &= 0b11111110; //Clear
    }

//Util functions
    virtual void Start(byte scalar = 0b001)
    {
        SetCS(scalar);
    }
    virtual void Stop()
    {
        SetCS(0);
    }
    virtual void Reset()
    {
        SetVal(0);
    }
};
#endif
