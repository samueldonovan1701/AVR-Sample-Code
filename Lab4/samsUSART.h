#ifndef SAMS_SERIAL
#define SAMS_SERIAL

#include <avr/io.h>
typedef volatile unsigned char reg;

struct USART
{
    reg* BRRL; //Baud Rate Register Lower//
    reg* BRRH; //Baud Rate Register Higher//
    reg* CSRA; //Control & Status Register A// [RxC,   TxC,   UDRE,  FE,   DOR,   PE,    U2X,   MPCM]
    reg* CSRB; //Control & Status Register B// [RXCIE, TXCIE, UDRIE, RXEN, TXEN,  UCSZ2, RXB8,  TXB8]
    reg* CSRC; //Control & Status Register C// [URSEL, UMSEL, UPM1,  UPM0, USBS,  UCSZ1, UCSZ0, UCPOL]
    reg* DR;   //Data Register//               [UDR[7:0]]
};

//USART Definitions//
USART USART0 = {.BRRL=&UBRR0L, .BRRH=&UBRR0H, .CSRA=&UCSR0A, .CSRB=&UCSR0B, .CSRC=&UCSR0C, .DR=&UDR0};
USART USART1 = {.BRRL=&UBRR1L, .BRRH=&UBRR1H, .CSRA=&UCSR1A, .CSRB=&UCSR1B, .CSRC=&UCSR1C, .DR=&UDR1};
USART USART2 = {.BRRL=&UBRR2L, .BRRH=&UBRR2H, .CSRA=&UCSR2A, .CSRB=&UCSR2B, .CSRC=&UCSR2C, .DR=&UDR2};
USART USART3 = {.BRRL=&UBRR3L, .BRRH=&UBRR3H, .CSRA=&UCSR3A, .CSRB=&UCSR3B, .CSRC=&UCSR3C, .DR=&UDR3};

//Function Prototypes//
bool USART_RxComplete(USART &U); //RxC (R)
bool USART_TxComplete(USART &U);  //TxC (R)
void USART_SetTxComplete(USART &U); //TxC (W 1)
void USART_ClearTxComplete(USART &U); //TxC (W 0)
bool USART_DataRegisterEmpty(USART &U); //UDRE (R)
bool USART_FrameError(USART &U); //FE (R)
bool USART_DataOverrunError(USART &U); //DOR (R)
bool USART_ParityError(USART &U); //PE (R)
bool USART_DoubleTransmissionSpeedIsEnabled(USART &U); //U2X (R)
void USART_EnableDoubleTransmissionSpeed(USART &U); //U2X (W 1)
void USART_DisableDoubleTransmissionSpeed(USART &U); //U2X (W 0)
bool USART_MultiProcessorCommunicationModeIsEnabled(USART &U); //MPCM (R)
void USART_EnableMultiProcessorCommunicationMode(USART &U); //MPCM (W 1)
void USART_DisableMultiProcessorCommunicationMode(USART &U); //MPCM (W 0)

//UCSRB//
bool USART_RxCompleteInterruptIsEnabled(USART &U); //RXCIE (R)
void USART_EnableRxCompleteInterrupt(USART &U); //RXCIE (W 1)
void USART_DisableRxCompleteInterrupt(USART &U); //RXCIE (W 0)
bool USART_TxCompleteInterruptIsEnabled(USART &U); //TXCIE (R)
void USART_EnableTxCompleteInterrupt(USART &U); //TXCIE (W 1)
void USART_DisableTxCompleteInterrupt(USART &U); //TXCIE (W 0)
bool USART_DataRegisterEmptyInterruptIsEnabled(USART &U); //UDRIE (R)
void USART_EnableDataRegisterEmptyInterrupt(USART &U); //UDRIE (W 1)
void USART_DisableDataRegisterEmptyInterrupt(USART &U); //UDRIE (W 0)
bool USART_RxIsEnabled(USART &U); //RXEN (R)
void USART_EnableRx(USART &U); //RXEN (W 1)
void USART_DisableRx(USART &U); //RXEN (W 0)
bool USART_TxIsEnabled(USART &U); //TXEN (R)
void USART_EnableTx(USART &U); //TXEN (W 1)
void USART_DisableTx(USART &U); //TXEN (W 0)
byte USART_RxBit9(USART &U); //RXB8 (R)
byte USART_TxBit9(USART &U); //TXB8 (R)
void USART_SetTxBit9(USART &U); //TXB8 (W 1)
void USART_ClearTxBit9(USART &U); //TXB8 (W 0)

//UCSRC//
#define USART_ASYNC 0b00
#define USART_SYNC  0b01
#define USART_MSPIM 0b11
byte USART_GetMode(USART &U); //UMSEL (R)
void USART_SetMode(USART &U, byte mode=USART_ASYNC); //UMSEL (W)

#define USART_PARITY_DISABLED 0b00
#define USART_PARITY_RESERVED 0b01
#define USART_PARITY_EVEN     0b10
#define USART_PARITY_ODD      0b11
byte USART_GetParity(USART &U); //UPM (R)
void USART_SetParity(USART &U, byte mode=USART_PARITY_DISABLED); //UPM (W)

#define USART_ONE_STOP_BIT 0b0
#define USART_TWO_STOP_BIT 0b1
byte USART_GetStopBits(USART &U); //USBS (R)
void USART_SetStopBits(USART &U, byte size=USART_ONE_STOP_BIT); //USBS (W)

#define USART_FIVE_BIT_FRAME 0b000
#define USART_SIX_BIT_FRAME 0b001
#define USART_SEVEN_BIT_FRAME 0b010
#define USART_EIGHT_BIT_FRAME 0b011
#define USART_NINE_BIT_FRAME 0b111
byte USART_GetFrameSize(USART &U); //UCSZ (R)
void USART_SetFrameSize(USART &U, byte size=USART_EIGHT_BIT_FRAME); //UCSZ (W) size must be between 5 and 9

#define USART_RISING_EDGE 0
#define USART_FALLING_EDGE 1
byte USART_GetClockPolarity(USART &U);
void USART_SetClockPolarity(USART &U, byte polarity=USART_RISING_EDGE);

//Core Funcs
void USART_SetBaudRate(USART &U, unsigned long BAUD_RATE);
void USART_Write(USART &U, byte data);
byte USART_Read(USART &U);




//Function Implementations//
//UCSRA//
//RxC (R)
bool USART_RxComplete(USART &U)
{
    return *U.CSRA & 0b10000000; // != 0
}

//TxC (W/R)
bool USART_TxComplete(USART &U)
{
    return *U.CSRA & 0b01000000; // != 0
}
void USART_SetTxComplete(USART &U)
{
    *U.CSRA |= 0b01000000;
}
void USART_ClearTxComplete(USART &U)
{
    *U.CSRA &= 0b10111111;
}

//UDRE (R)
bool USART_DataRegisterEmpty(USART &U)
{
    return *U.CSRA & 0b00100000; //!= 0
}

//FE (R)
bool USART_FrameError(USART &U)
{
    return *U.CSRA & 0b00010000; //!= 0
}

//DOR (R)
bool USART_DataOverrunError(USART &U)
{
    return *U.CSRA & 0b00001000; //!= 0
}

//PE (R)
bool USART_ParityError(USART &U)
{
    return *U.CSRA & 0b00000100; //!= 0
}

//U2X (R/W)
bool USART_DoubleTransmissionSpeedIsEnabled(USART &U)
{
    return *U.CSRA & 0b00000010; //!= 0
}
void USART_EnableDoubleTransmissionSpeed(USART &U)
{
    *U.CSRA |= 0b00000010;
} 
void USART_DisableDoubleTransmissionSpeed(USART &U)
{   
    *U.CSRA &= 0b11111101;
}

//MPCM (R/W)
bool USART_MultiProcessorCommunicationModeIsEnabled(USART &U)
{
    return *U.CSRA & 0b00000001;
}
void USART_EnableMultiProcessorCommunicationMode(USART &U)
{
    *U.CSRA |= 0b00000001;
}
void USART_DisableMultiProcessorCommunicationMode(USART &U)
{
    *U.CSRA &= 0b11111110;
}




//UCSRB//
//RXCIE (R/W)
bool USART_RxCompleteInterruptIsEnabled(USART &U)
{
    return *U.CSRB & 0b10000000; //!= 0
}
void USART_EnableRxCompleteInterrupt(USART &U)
{
   *U.CSRB |= 0b10000000;
}
void USART_DisableRxCompleteInterrupt(USART &U)
{
    *U.CSRB &= 0b01111111;
}

//TXCIE (R/W)
bool USART_TxCompleteInterruptIsEnabled(USART &U)
{
    return *U.CSRB & 0b01000000; //!= 0
}
void USART_EnableTxCompleteInterrupt(USART &U)
{
    *U.CSRB |= 0b01000000;
}
void USART_DisableTxCompleteInterrupt(USART &U)
{
    *U.CSRB &= 0b10111111;
}

//UDRIE (R/W)
bool USART_DataRegisterEmptyInterruptIsEnabled(USART &U)
{
    return *U.CSRB & 0b00100000; //!= 0
}
void USART_EnableDataRegisterEmptyInterrupt(USART &U)
{
    *U.CSRB |= 0b00100000;
}
void USART_DisableDataRegisterEmptyInterrupt(USART &U)
{
    *U.CSRB &= 0b11011111;
}

//RXEN (R/W)
bool USART_RxIsEnabled(USART &U)
{
    return *U.CSRB & 0b00010000; //!= 0
}
void USART_EnableRx(USART &U)
{
    *U.CSRB |= 0b00010000;    
}
void USART_DisableRx(USART &U)
{
    *U.CSRB &= 0b11101111;
}

//TXEN (R/W)
bool USART_TxIsEnabled(USART &U)
{
    return *U.CSRB & 0b00001000; //!= 0
}
void USART_EnableTx(USART &U)
{
    *U.CSRB |= 0b00001000;
}
void USART_DisableTx(USART &U)
{
    *U.CSRB &= 0b11110111;
}

//UCSZ2 (R/W) (See FrameSize funcs)

//RXB8 (R)
byte USART_RxBit9(USART &U)
{
    return (*U.CSRB & 0b00000010) >> 1;
}
byte USART_TxBit9(USART &U)
{
    return *U.CSRB & 0b00000001;
}
void USART_SetTxBit9(USART &U)
{
    *U.CSRB |= 0b00000001;
}
void USART_ClearTxBit9(USART &U)
{
    *U.CSRB &= 0b11111110;
}





//UCSRC//
//UMSEL (R/W)
byte USART_GetMode(USART &U)
{
    return (*U.CSRC & 0b11000000) >> 6;
}
void USART_SetMode(USART &U, byte mode)
{
    *U.CSRC &= 0b00111111; //Clear
    *U.CSRC |= (mode & 0b11) << 6; //Set
}

//UPM (R/W)
byte USART_GetParity(USART &U)
{
    return (*U.CSRC & 0b00110000) >> 4;
}
void USART_SetParity(USART &U, byte mode)
{
    *U.CSRC &= 0b11001111; //Clear
    *U.CSRC |= (mode & 0b11) << 4; //Set
}

//USBS (R/W)
byte USART_GetStopBits(USART &U)
{
    return (*U.CSRC & 0b00001000) >> 3;
}
void USART_SetStopBits(USART &U, byte size)
{
    *U.CSRC &= 0b11110111; //Clear
    *U.CSRC |= (size & 0b1) << 3; //Set
}

//UCSZ (R/W)
byte USART_GetFrameSize(USART &U)
{
    return (*U.CSRB & 0b00000100) + ((*U.CSRC & 0b00000110) >> 1);
}
void USART_SetFrameSize(USART &U, byte size) //size can be 5-9 bits
{
    *U.CSRC &= 0b11111001; //Clear UCSZ 0 & 1
    *U.CSRB &= 0b11111011; //Clear UCSZ 2

    if(size == 9)
        size = 0b111;
    else
        size = size - 5;
    
    *U.CSRC |= (size & 0b011) << 1; //Set UCSZ 0 & 1
    *U.CSRC |= (size & 0b100); //Set UCSZ 2
}

//UCPOL
byte USART_GetClockPolarity(USART &U)
{
    return *U.CSRC & 0b00000001;
}
void USART_SetClockPolarity(USART &U, byte polarity)
{
    *U.CSRC &= 0b11111110; //Clear
    *U.CSRC |= polarity & 0b1; //Set
}


//Core Funcs
void USART_SetBaudRate(USART &U, unsigned long baud_rate)
{
    unsigned short val = 0;
    
    if(USART_GetMode(U) == USART_SYNC) //SYNC
        val = F_CPU/(2UL*baud_rate)-1;
    else if(USART_DoubleTransmissionSpeedIsEnabled(U)) //Double ASYNC
        val = F_CPU/(8UL*baud_rate)-1;
    else //ASYNC
        val = F_CPU/(16UL*baud_rate)-1;
    
    *U.BRRH = (val >> 8) & 0b00001111; //Set URBBH
    *U.BRRL = val; //Set UBRRL
}

void USART_Write(USART &U, byte data)
{
    *U.DR = data;
}
byte USART_Read(USART &U)
{
    return *U.DR;
}

#endif
