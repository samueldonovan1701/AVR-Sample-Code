#include "samsUSART.h"
#include "samsMAX7219.h"
#include "samsMatrixDisplay.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


MAX7219 led = 
{
    .DIN = {.DDR=&DDRH, .PORT_OUT=&PORTH, .PORT_IN=&PINH, .PIN=5}, //Pin 8
    .CS = {.DDR=&DDRH, .PORT_OUT=&PORTH, .PORT_IN=&PINH, .PIN=6},  //Pin 9
    .CLK = {.DDR=&DDRB, .PORT_OUT=&PORTB, .PORT_IN=&PINB, .PIN=4} //Pin 10   
};

void max7219Setup(){
    MAX7219_SetupGPIO(led);
    MAX7219_TurnOn(led);
    MAX7219_Clear(led);
    MAX7219_SetScanLimit(led, 8);
}

void serialSetup()
{
    USART_SetBaudRate(USART0, 9600);
    USART_SetFrameSize(USART0, 8);
    USART_SetStopBits(USART0, USART_ONE_STOP_BIT);
    USART_SetParity(USART0, USART_PARITY_DISABLED);
    USART_EnableRxCompleteInterrupt(USART0);
    USART_EnableRx(USART0);
    USART_EnableTx(USART0);
}


#define BUFFER_SIZE 80
char buffer[BUFFER_SIZE];
volatile int bufferStart = 0;
volatile int bufferEnd = 0;

ISR(USART0_RX_vect)
{
    char c = USART_Read(USART0);
    USART_Write(USART0, c); //Echo
    if(isalpha(c) || isdigit(c))
    {
        buffer[bufferEnd] = c; //Store
        bufferEnd++; //Increment end point
        if(bufferEnd == BUFFER_SIZE) //Loop
            bufferEnd = 0;
    }
}

int main()
{    
    max7219Setup();
    serialSetup();
    sei();
    
    while(1)
    {
        while(bufferStart != bufferEnd)
        {
            MAX7219_Clear(led);
            _delay_ms(200);
            MATRIX_WriteChar(led, buffer[bufferStart]); //Wite to LED

            bufferStart++; //Increment start point
            if(bufferStart == BUFFER_SIZE) //Loop
                bufferStart = 0;
                
            _delay_ms(1000);
        }
    }
}
