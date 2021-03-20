#ifndef SAMS_LCD
#define SAMS_LCD

#include "samsGPIO.h"
#include <avr/io.h>
#include <util/delay.h>

class LCD
{
public:
//GPIO Pins
    GPIO RS; //Register Select Pin (1 = Data Input | 0 = Instruction Input)
    GPIO RW; //Read/Write Select Pin (1 = Read | 0 = Write) 
    GPIO E;  //Enable Signal Pin
    GPIO D[4]; //Data Pins

//Class
    LCD();
    LCD(GPIO RS, GPIO RW, GPIO E, GPIO D[]);
    
//Core
    bool IsBusy();
    byte ReadAddress();
    byte ReadData();
    void WriteData(byte data);
    void WriteInstruction(byte instruction);
//Base Functions
    void Clear();
    void ReturnHome();
    void SetEntryMode(bool increment, bool entireShift=false);
    void DisplayControl(bool on, bool cursor=true, bool blink=true);
    void ShiftCursorLeft();
    void ShiftCursorRight();
    void ShiftDisplayLeft();
    void ShiftDisplayRight();
    void SetFunction(bool twoLineMode=true, bool fontType11=false);
    void SetCGRAMAddress(byte addr);
    void SetDDRAMAddress(byte addr);
//Convience
    void SetPos(byte line = 1, byte pos = 0);
    void Write(byte c, byte line = 0, byte pos = 0);
    void Write(char* buffer, byte line = 0, byte pos = 0, byte wrapAt = -1);
    void AddCustomChar(byte charCode, byte* bitMap);
};
#endif
