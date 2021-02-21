#ifndef SAMS_8X8_Display
#define SAMS_8X8_Display
#include "samsLEDDisplay.h"
#include "CharLUT.h"


#define ROW_NO_OP 0b0000
#define ROW_0 0b0001
#define ROW_1 0b0010
#define ROW_2 0b0011
#define ROW_3 0b0100
#define ROW_4 0b0101
#define ROW_5 0b0110
#define ROW_6 0b0111
#define ROW_7 0b1000

void SetRow(LED_Display &disp, byte row, byte data);
void WriteChar(LED_Display &disp, unsigned char x);


void SetRow(LED_Display &disp, byte row, byte data)
{ 
  SendData(disp, row, data);
}

void WriteChar(LED_Display &disp, unsigned char x)
{
  int loc = 0;
  if(isalpha(x))
  {  
    x = toupper(x);
    loc = x - 55;
  }
  else if(isdigit(x))
  {
    loc = x - 48;
  }
  else
  {
    loc = 36;
  }
  SetRow(disp, ROW_0, CharTable[loc][0]);
  SetRow(disp, ROW_1, CharTable[loc][1]);
  SetRow(disp, ROW_2, CharTable[loc][2]);
  SetRow(disp, ROW_3, CharTable[loc][3]);
  SetRow(disp, ROW_4, CharTable[loc][4]);
  SetRow(disp, ROW_5, CharTable[loc][5]);
  SetRow(disp, ROW_6, CharTable[loc][6]);
  SetRow(disp, ROW_7, CharTable[loc][7]);
}


#endif
