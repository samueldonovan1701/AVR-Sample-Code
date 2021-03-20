#ifndef MULT_SEV_SEG
#define MULT_SEV_SEG
#include "avr-GPIO/GPIO.h"

class MultSevSeg
{
private:
	GPIO* Pin;
	GPIO* GND;
	byte* currentVal;
    byte* DP;
	byte N;
     
    byte LUT[17][7] =
    {
        {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW},  //0
        {LOW,  HIGH, HIGH, LOW,  LOW,  LOW,  LOW},  //1
        {HIGH, HIGH, LOW,  HIGH, HIGH, LOW,  HIGH}, //2
        {HIGH, HIGH, HIGH, HIGH, LOW,  LOW,  HIGH}, //3
        {LOW,  HIGH, HIGH, LOW,  LOW,  HIGH, HIGH}, //4
        {HIGH, LOW,  HIGH, HIGH, LOW,  HIGH, HIGH}, //5
        {HIGH, LOW,  HIGH, HIGH, HIGH, HIGH, HIGH}, //6
        {HIGH, HIGH, HIGH, LOW,  LOW,  LOW,  LOW},  //7
        {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH}, //8
        {HIGH, HIGH, HIGH, HIGH, LOW,  HIGH, HIGH}, //9
        {HIGH, HIGH, HIGH, LOW,  HIGH, HIGH, HIGH}, //A
        {LOW,  LOW,  HIGH, HIGH, HIGH, HIGH, HIGH}, //B
        {HIGH, LOW,  LOW,  HIGH, HIGH, HIGH, LOW},  //C
        {LOW,  HIGH, HIGH, HIGH, HIGH, LOW,  HIGH}, //D
        {HIGH, LOW,  LOW,  HIGH, HIGH, HIGH, HIGH}, //E
        {HIGH, LOW,  LOW,  LOW,  HIGH, HIGH, HIGH}, //F
        {LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW}   //Clear
    };
    
public:

	MultSevSeg(GPIO* Pins, GPIO* Grounds, byte count);
    void Cycle();
	void Write(byte index, byte num);
    void WriteNum(unsigned long num, byte base = 16);
    void WriteChar(byte index, char c);
    void WriteStr(char* str);
    void Clear(byte index);


};


#endif
