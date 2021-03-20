#include "multiSevSeg.h"
#include <util/delay.h>
#include <string.h>
//  GPIO* Pin;
//  GPIO* GND;
//  byte* currentVal;
//  byte N;

MultSevSeg::MultSevSeg(GPIO* Pins, GPIO* Grounds, byte count)
{
    this->Pin = Pins;
    this->GND = Grounds;
    this->N = count;  
    this->currentVal = new byte[count];
    this->DP = new byte[count];

    //Set as outputs
    for(byte p=0; p < 8; p++)
    {
        Pin[p].Output();
        Pin[p].Clear();
    }
    for(byte d=0; d < count; d++)
    {
        GND[d].Output();
        GND[d].Set(); //Turn off
        DP[d] = LOW;
    }
}


void MultSevSeg::Write(byte index, byte num)
{
    if(num > 0xF)
        Clear(index);
    else
        this->currentVal[index] = num;
}

void MultSevSeg::WriteNum(unsigned long num, byte base)
{
    for(byte b = 0; b < this->N; b++)
    {
        Write(b, num & (base - 1));
        num /= base;
    }
}

void MultSevSeg::WriteChar(byte index, char c)
{
    if(c == '.')
        DP[index] = HIGH;
    else if(c >= '0' && c <= '9')
        Write(index, c - 48);
    else if(c >= 'a' && c <= 'f')
        Write(index, c - 87);
    else if(c >= 'A' && c <= 'F')
        Write(index, c - 55);
    else
        Clear(index);
}

void MultSevSeg::WriteStr(char* str)
{
    //Clear all DP
    for(byte i = 0; i < this->N; i++)
        this->DP[i] = LOW;
    
    strrev(str);

    byte digit = 0;
    for(byte i = 0; str[i] != 0; i++)
    {
        WriteChar(digit, str[i]);
        
        if(str[i] != '.')
            digit++;
    }
}

void MultSevSeg::Clear(byte index)
{
    currentVal[index] = 0x10;
}

void MultSevSeg::Cycle()
{
    for(byte d=0; d < this->N; d++)
    {
        byte val = currentVal[d];
        byte* matrix = LUT[val];

        //Set pins
        Pin[0].Write(matrix[0]);
        Pin[1].Write(matrix[1]);
        Pin[2].Write(matrix[2]);
        Pin[3].Write(matrix[3]);
        Pin[4].Write(matrix[4]);
        Pin[5].Write(matrix[5]);
        Pin[6].Write(matrix[6]);
        Pin[7].Write(DP[d]);

        //Ground (turn on)
        GND[d].Clear();
        
        //Wait
        _delay_ms(500);

        //Unground (turn off)
        GND[d].Set();
    }
}
