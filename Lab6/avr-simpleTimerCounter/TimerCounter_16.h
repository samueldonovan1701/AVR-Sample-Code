#ifndef SIMPLE_TIMERCOUNTER_16
#define SIMPLE_TIMERCOUNTER_16

typedef uint8_t byte;
typedef volatile byte reg;


class TimerCounter_16 : public TimerCounter<uint16_t>
{
protected:
//Registers
    reg* TCNTnL; //Timer Value Low Nibble
    reg* TCNTnH; //Timer Value High Nibble

    reg* TCCRnC; //Control Register C

    reg* OCRnAL; //Output Compare Register A Low Nibble
    reg* OCRnAH; //Output Compare Register A High Nibble
    reg* OCRnBL; //Output Compare Register B Low Nibble
    reg* OCRnBH; //Output Compare Register B High Nibble
    reg* OCRnCL; //Output Compare Register C Low Nibble
    reg* OCRnCH; //Output Compare Register C High Nibble

    reg* TIMSKn; //Interrupt Mask Register

public:
//Contructor
    TimerCounter_16(reg* TCNTnL, reg* TCNTnH,  reg* TCCRnA, reg* TCCRnB, reg* TCCRnC, reg* OCRnAL, reg* OCRnAH, reg* OCRnBL, reg* OCRnBH, reg* OCRnCL, reg* OCRnCH, reg* TIMSKn)
        : TimerCounter(TCNTnL, TCCRnA, TCCRnB, OCRnAL, OCRnBL, TIMSKn)
    {
        this->TCNTnL = TCNTnL;
        this->TCNTnH = TCNTnH;

        this->TCCRnC = TCCRnC;

        this->OCRnAL = OCRnAL;
        this->OCRnAH = OCRnAH;
        this->OCRnBL = OCRnBL;
        this->OCRnBH = OCRnBH;
        this->OCRnCL = OCRnCL;
        this->OCRnCH = OCRnCH;
    }

//TCNTn
    void SetVal(uint16_t val) override //change to 16-bit
    {
        *TCNTnL = val;
        *TCNTnH = (val >> 8);
    }
    uint16_t GetVal() override //change to 16-bit
    {
        return (*TCNTnH << 8) | *TCNTn;
    }

//TCCRnA
    void SetCOM(byte mask, char channel = 'A')  override //Add channel C
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
            case 'C':  //COMnC 1:0 | TCCRnA 3:2
                *TCCRnA &= 0b11110011;  //Clear
                *TCCRnA |= (mask << 2);    //Set
                return;
            default:
                return;    
        }
    }
    byte GetCOM(char channel = 'A') override //Add Channel C
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
            case 'C':  //COMnC 1:0 | TCCRnA 3:2
                mask = (*TCCRnA >> 2 ) & 0b11;
                break;
            default:
                mask =  -1;    
        };

        return mask;
    }

    void SetWGM(byte mask) override //Add WGM 3
    {
        mask &= 0b1111; //Truncate
        
        //WGMn 1:0 | TCCRnA 1:0
        *TCCRnA &= 0b11111100;  //Clear
        *TCCRnA |= (mask & 0b0011); //Set

        //WGM 3:2 | TCCRnB 4:3
        *TCCRnB &= 0b11100111;  //Clear
        *TCCRnB |= ((mask & 0b1100) << 1); // Set
    }
    byte GetWGM() override //Add WGM 3
    {
        byte mask;

        //WGMn 1:0 | TCCRnA 1:0
        mask = *TCCRnA & 0b0011;

        //WGM 3:2 | TCCRnB 4:3
        mask |= (*TCCRnB >> 1) & 0b1100; 

        return mask;
    }

//TCCRnB
    void EnableInputNoiseCancellation()
    {
        //ICNCn | TCCRnB 7
        *TCCRnB |= 0b10000000; //Set
    }
    void DisableInputNoiseCancellation()
    {
        //ICNCn | TCCRnB 7
        *TCCRnB &= 0b01111111; //Clear
    }

    void InputCaptureOnRise()
    {
        //ICESn | TCCRnB 6
        *TCCRnB |= 0b01000000; //Set
    }
    void InputCaptureOnFall()
    {
        //ICESn | TCCRnB 6
        *TCCRnB &= 0b10111111; //Clear
    }

    //SetCS(byte) is the same

//TCCRnC (new)
    void ForceOutput(char channel = 'A') //Add channel C; new CR
    {
        
        switch(channel)
        {
            case('A'): //FOCnA | TCCRnC 7
                *TCCRnC |= 0b10000000;
                return;
            case('B'): //FOCnB | TCCRnC 6
                *TCCRnC |= 0b01000000;
                return;
            case('C'): //FOCnC | TCCRnC 5
                *TCCRnC |= 0b00100000;
                return;
            default:
                return;
        }
    }

//OCRnx
    void SetOCR(uint16_t val, char channel = 'A') override //Add channel C, change to 16-bit
    {
        switch(channel)
        {
            case('A'):
                *OCRnAL = val;
                *OCRnAH = (val >> 8);
                return;
            case('B'):
                *OCRnBL = val;
                *OCRnBH = (val >> 8);
                return;
            case('C'):
                *OCRnCL = val;
                *OCRnCH = (val >> 8);
                return;
            default:
                return;
        }
    }
    uint16_t GetOCR(char channel='A') //Add channel C, change to 16-bit
    {
        switch(channel)
        {
            case('A'):
                return (*OCRnAH << 8) | *OCRnAL;
            case('B'):
                return (*OCRnBH << 8) | *OCRnBL;
            case('C'):
                return (*OCRnCH << 8) | *OCRnCL;
            default:
                return -1;
        }
    }
};
#endif
