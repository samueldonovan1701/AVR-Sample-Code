#ifndef SAMS_LED_Display
#define SAMS_LED_Display
#include "samsGPIO.h"

struct LED_Display
{
    GPIO DIN;
    GPIO CS;
    GPIO CLK;
};

//Core Functions//
void SetupGPIOLED(LED_Display &disp);
void SendMSBLED(LED_Display &disp, byte b);
void SendByteLED(LED_Display &disp, byte b);
void SendDataLED(LED_Display &disp, byte addr, byte data);
void ClearLED(LED_Display &disp);
//General Functions//
void TurnOffLED(LED_Display &disp);
void TurnOnLED(LED_Display &disp);
#define BCD_DECODING 0b11111111
#define NO_DECODING  0b00000000
void SetDecodingLED(LED_Display &disp, byte mode=NO_DECODING);
void SetIntensityLED(LED_Display &disp, byte intensity=0); //intensity = [0, 15]
void SetScanLimitLED(LED_Display &disp, byte nOutputs=8); //nOutputs = [1, 8]
void StartTestLED(LED_Display &disp);
void StopTestLED(LED_Display &disp);


//Addresses
#define ADDR_NO_OP 0b0000
#define ADDR_DIGIT_0 0b0001
#define ADDR_DIGIT_1 0b0010
#define ADDR_DIGIT_2 0b0011
#define ADDR_DIGIT_3 0b0100
#define ADDR_DIGIT_4 0b0101
#define ADDR_DIGIT_5 0b0110
#define ADDR_DIGIT_6 0b0111
#define ADDR_DIGIT_7 0b1000
#define ADDR_DECODE_MODE 0b1001
#define ADDR_INTENSITY 0b1010
#define ADDR_SCAN_LIMIT 0b1011
#define ADDR_SHUTDOWN 0b1100
#define ADDR_DISPLAY_TEST 0b1111

//Core Functions//
void SetupGPIOLED(LED_Display &disp)
{
	SetMode(disp.DIN, OUTPUT);
	SetMode(disp.CS, OUTPUT);
	SetMode(disp.CLK, OUTPUT);
}

void SendMSBLED(LED_Display &disp, byte b)
{
	SetState(disp.CLK, 0);
	SetState(disp.DIN, (b >> 7));
	SetState(disp.CLK, 1);
}

void SendByteLED(LED_Display &disp, byte b)
{
	SendMSB(disp, b << 0); //7th bit
    SendMSB(disp, b << 1); //6th bit
    SendMSB(disp, b << 2); //5th bit
    SendMSB(disp, b << 3); //4th bit
    SendMSB(disp, b << 4); //3th bit
    SendMSB(disp, b << 5); //2th bit
    SendMSB(disp, b << 6); //1th bit
    SendMSB(disp, b << 7); //0th bit
}

void SendDataLED(LED_Display &disp, byte addr, byte data)
{ 
	SetState(disp.CS, 0);
	SendByte(disp, addr);
	SendByte(disp, data);
	SetState(disp.CS, 1);
}

void ClearLED(LED_Display &disp)
{
	SendData(disp, ADDR_DIGIT_0, 0);
	SendData(disp, ADDR_DIGIT_1, 0);
	SendData(disp, ADDR_DIGIT_2, 0);
	SendData(disp, ADDR_DIGIT_3, 0);
	SendData(disp, ADDR_DIGIT_4, 0);
	SendData(disp, ADDR_DIGIT_5, 0);
	SendData(disp, ADDR_DIGIT_6, 0);
	SendData(disp, ADDR_DIGIT_7, 0);
    StopTest(disp);
}

//General Functions//
//Shutdown Register//
void TurnOffLED(LED_Display &disp)
{
	SendDataLED(disp, ADDR_SHUTDOWN, 0b00000000);
}
void TurnOnLED(LED_Display &disp)
{
	SendData(disp, ADDR_SHUTDOWN, 0b00000001);
}

//Decode Mode Register//
void SetDecodingLED(LED_Display &disp, byte mode)
{
	SendData(disp, ADDR_DECODE_MODE, mode);
}

//Intensity Register//
void SetIntensityLED(LED_Display &disp, byte intensity) //intensity = [0, 15]
{
	SendData(disp, ADDR_INTENSITY, intensity);
}

//Scan Limit Register// (Sets how many outputs are disped/written to)
void SetScanLimitLED(LED_Display &disp, byte nOutputs) //nOutputs = [1, 8]
{
	nOutputs--;
	SendData(disp, ADDR_SCAN_LIMIT, nOutputs);
}

void StartTestLED(LED_Display &disp)
{
	SendData(disp, ADDR_DISPLAY_TEST, 1);
}

void StopTestLED(LED_Display &disp)
{
	SendData(disp, ADDR_DISPLAY_TEST, 0);
}

#endif
