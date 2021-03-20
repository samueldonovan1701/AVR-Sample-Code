#ifndef SAMS_MATRIX_DISPLAY
#define SAMS_MATRIX_DISPLAY
#include "samsMAX7219.h"
#include "MatrixDisplayCharLUT.h"


void MATRIX_SetRow(MAX7219 &disp, byte row, byte data);
void MATRIX_WriteChar(MAX7219 &disp, unsigned char x);


void MATRIX_SetRow(MAX7219 &disp, byte row, byte data)
{ 
  if(row < 8)
    MAX7219_SendData(disp, row+1, data);
}

void MATRIX_WriteChar(MAX7219 &disp, unsigned char x)
{
  int loc = 0;
  int i = 0;
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


  for(i = 0; i < 8; i++)
    MATRIX_SetRow(disp, i, CharTable[loc][i]);
}


#endif
