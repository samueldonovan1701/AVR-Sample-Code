#include "samsLCD.h"
#include <avr/io.h>
#include <util/delay.h>


//Class
LCD::LCD()
{

}
LCD::LCD(GPIO RS, GPIO RW, GPIO E, GPIO D[])
{
  //Setup GPIO
  this->RS = RS;
  this->RW = RW;
  this->E = E;

  RS.SetMode(OUTPUT);
  RW.SetMode(OUTPUT);
  E.SetMode(OUTPUT);
 
  
  for(int i=0; i < 4; i++)
  {
    this->D[i] = D[i];
    D[i].SetMode(OUTPUT);
  }

    //Prepare Instruction Write
    E.Clear();
    RS.Clear();
    RW.Clear();

    //Wait at least 30ms after Vdd rises to 4.5V
    _delay_ms(100);

    //Reset (Function Set to 8-bit mode) //Set D7:D4 to [0011]
    D[3].Clear();
    D[2].Clear();
    D[1].Set();
    D[0].Set();
    E.Set();
    _delay_us(1);
    E.Clear();

    //Execution Time: 39us
    _delay_us(50);
    
    //Enable 4-bit (Function Set to 4-bit mode) //Set D7:D4 to [0010]
    D[3].Clear();
    D[2].Clear();
    D[1].Set();
    D[0].Clear();
    E.Set();
    _delay_us(1);
    E.Clear();

    //Execution Time: 39us
    _delay_us(50);

    //Init Sequence: See documentation pg. 27
    SetFunction(true, false); //Function Set, 2-line mode, font 8
    
    DisplayControl(true, true, true); //Display ON, Cursor ON, Blink ON
    
    Clear();

    SetEntryMode(true, false); //Increment mode, Entire shift OFF
}

//Core
bool LCD::IsBusy()
{
    RS.Clear();
    E.Clear();
    RW.Clear();

    D[3].Input();
    bool b = D[3].GetState(); 
    D[3].Output();
    
    return b;
}
byte LCD::ReadAddress()
{ 
  byte b = 0;
    
  //Prepare Read Address
  E.Clear();
  RS.Clear();
  RW.Set();
  D[3].Input();
  D[2].Input();
  D[1].Input();
  D[0].Input();

  //Execution Time: 0us  
  
  //Read high nibble
  E.Set();
  _delay_us(1);
  if(D[3].GetState())
    b |= 1;
  b = b << 1;
  if(D[2].GetState())
    b |= 1;
  b = b << 1;
  if(D[1].GetState())
    b |= 1;
  b = b << 1;
  if(D[0].GetState())
    b |= 1;
  b = b << 1;
  E.Clear();
  _delay_us(1);

  //Read low nibble
  E.Set();
  _delay_us(1);
  if(D[3].GetState())
    b |= 1;
  b = b << 1;
  if(D[2].GetState())
    b |= 1;
  b = b << 1;
  if(D[1].GetState())
    b |= 1;
  b = b << 1;
  if(D[0].GetState())
    b |= 1;
  b = b << 1;
  E.Clear();
  _delay_us(1);


  //Cleanup
  D[3].Output();
  D[2].Output();
  D[1].Output();
  D[0].Output();

  return b;
}
byte LCD::ReadData()
{  
  byte b = 0;
  
  //Wait until not busy
  while(IsBusy()){};
    
  //Prepare Read Data
  E.Clear();
  RS.Set();
  RW.Set();
  D[3].Input();
  D[2].Input();
  D[1].Input();
  D[0].Input();

  //Execution Time: 43us
  _delay_us(50);

  
  
  //Read high nibble
  E.Set();
  _delay_us(1);
  if(D[3].GetState())
    b |= 1;
  b = b << 1;
  if(D[2].GetState())
    b |= 1;
  b = b << 1;
  if(D[1].GetState())
    b |= 1;
  b = b << 1;
  if(D[0].GetState())
    b |= 1;
  b = b << 1;
  E.Clear();
  _delay_us(1);

  //Read low nibble
  E.Set();
  _delay_us(1);
  if(D[3].GetState())
    b |= 1;
  b = b << 1;
  if(D[2].GetState())
    b |= 1;
  b = b << 1;
  if(D[1].GetState())
    b |= 1;
  b = b << 1;
  if(D[0].GetState())
    b |= 1;
  b = b << 1;
  E.Clear();
  _delay_us(1);


  //Cleanup
  D[3].Output();
  D[2].Output();
  D[1].Output();
  D[0].Output();

  return b;
}
void LCD::WriteData(byte data)
{
  //Prepare Write Data
  E.Clear();
  RS.Set();
  RW.Clear();
  
  //Write high nibble
  D[3].SetState(data & 0b10000000);
  D[2].SetState(data & 0b01000000);
  D[1].SetState(data & 0b00100000);
  D[0].SetState(data & 0b00010000);
  E.Set();
  _delay_us(1);
  E.Clear();
  _delay_us(1);


  //Write low nibble
  D[3].SetState(data & 0b00001000);
  D[2].SetState(data & 0b00000100);
  D[1].SetState(data & 0b00000010);
  D[0].SetState(data & 0b00000001);
  E.Set();
  _delay_us(1);
  E.Clear();

  _delay_us(50); //Execution Time: 43us
}
void LCD::WriteInstruction(byte instruction)
{
  //Prepare Write Instruction
  E.Clear();
  RS.Clear();
  RW.Clear();

  //Write high nibble
  D[3].SetState(instruction & 0b10000000);
  D[2].SetState(instruction & 0b01000000);
  D[1].SetState(instruction & 0b00100000);
  D[0].SetState(instruction & 0b00010000);
  E.Set();
  _delay_us(1);
  E.Clear();
  _delay_us(1);


  //Write low nibble
  D[3].SetState(instruction & 0b00001000);
  D[2].SetState(instruction & 0b00000100);
  D[1].SetState(instruction & 0b00000010);
  D[0].SetState(instruction & 0b00000001);
  E.Set();
  _delay_us(1);
  E.Clear();
}


//Functions
void LCD::Clear()
{
    WriteInstruction(0b00000001);
    _delay_ms(2); //Execution Time: 1.53ms
}
void LCD::ReturnHome()
{
    WriteInstruction(0b00000010);
    _delay_ms(2); //Execution Time: 1.53ms
}
void LCD::SetEntryMode(bool increment, bool entireShift)
{
    byte instruction = 0b00000100;
    
    if(increment)
        instruction |= 0b10;
    if(entireShift)
        instruction |= 0b01;

    WriteInstruction(instruction);
    
    _delay_us(50); //Execution Time: 39us
}
void LCD::DisplayControl(bool on, bool cursor, bool blink)
{
    byte instruction = 0b00001000;
    
    if(on)
        instruction |= 0b100;
    if(cursor)
        instruction |= 0b010;
    if(blink)
        instruction |= 0b001;

    WriteInstruction(instruction);
    
    _delay_us(50); //Execution Time: 39us
}
void LCD::ShiftCursorLeft()
{
    WriteInstruction(0b00010000);
    
    _delay_us(50); //Execution Time: 39us
}
void LCD::ShiftCursorRight()
{
    WriteInstruction(0b00010100);

    
    _delay_us(50); //Execution Time: 39us
}
void LCD::ShiftDisplayLeft()
{
    WriteInstruction(0b00011000);
    
    _delay_us(50); //Execution Time: 39us
}
void LCD::ShiftDisplayRight()
{
    WriteInstruction(0b00011100);
    
    _delay_us(50); //Execution Time: 39us
}
void LCD::SetFunction(bool twoLineMode, bool fontType11)
{
    byte instruction = 0b00100000;
    
    if(twoLineMode)
        instruction |= 0b01000;
    if(fontType11)
        instruction |= 0b00100;

    WriteInstruction(instruction);

    _delay_us(50); //Execution Time: 39us
}
void LCD::SetCGRAMAddress(byte addr)
{
    byte instruction = 0b01000000;
    
    instruction |= (addr & 0b00111111);
    
    WriteInstruction(instruction);

    _delay_us(50); //Execution Time: 39us
}
void LCD::SetDDRAMAddress(byte addr)
{
    byte instruction = 0b10000000;
    
    instruction |= (addr & 0b01111111);
    
    WriteInstruction(instruction);

    _delay_us(50); //Execution Time: 39us
}

//Convience
void LCD::SetPos(byte line, byte pos)
{
    if(line == 2)
        pos += 0x40;

    SetDDRAMAddress(pos);    
}
void LCD::Write(byte c, byte line, byte pos)
{
    if(line != 0)
        SetPos(line, pos);
        
    WriteData(c);
}
void LCD::Write(char* buffer, byte line, byte pos, byte wrapAt)
{
    if(line != 0)
        SetPos(line, pos);
    
    for(byte i = 0; buffer[i] != 0; i++)
    {
        Write(buffer[i]);
        if(i == wrapAt)
            SetPos(2, 0);
    }    
}
void LCD::AddCustomChar(byte charCode, byte bitMap[])
{
    if(charCode > 7)
        return;
        
    SetCGRAMAddress(charCode * 8); //Each char mask takes up 8 bytes

    for(byte i = 0; i < 8; i++)
        WriteData(bitMap[i]);

    SetPos(1, 0);
}
