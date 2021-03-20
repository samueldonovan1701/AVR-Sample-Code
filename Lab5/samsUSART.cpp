#include "samsUSART.h"

//USART Definitions
USART USART0 = USART(&UBRR0L, &UBRR0H, &UCSR0A, &UCSR0B, &UCSR0C, &UDR0);
USART USART1 = USART(&UBRR1L, &UBRR1H, &UCSR1A, &UCSR1B, &UCSR1C, &UDR1);
USART USART2 = USART(&UBRR2L, &UBRR2H, &UCSR2A, &UCSR2B, &UCSR2C, &UDR2);
USART USART3 = USART(&UBRR3L, &UBRR3H, &UCSR3A, &UCSR3B, &UCSR3C, &UDR3);

//Class
USART::USART(reg* UBRRL, reg* UBRRH, reg* UCSRA, reg* UCSRB, reg* UCSRC, reg* UDR)
{
    BRRL = UBRRL;
    BRRH = UBRRH;
    CSRA = UCSRA;
    CSRB = UCSRB;
    CSRC = UCSRC;
    DR = UDR;
}

//UCSRA//
//RxC (R)
bool USART::RxComplete()
{
    return *CSRA & 0b10000000; // != 0
}

//TxC (W/R)
bool USART::TxComplete()
{
    return *CSRA & 0b01000000; // != 0
}
void USART::SetTxComplete()
{
    *CSRA |= 0b01000000;
}
void USART::ClearTxComplete()
{
    *CSRA &= 0b10111111;
}

//UDRE (R)
bool USART::DataRegisterEmpty()
{
    return *CSRA & 0b00100000; //!= 0
}

//FE (R)
bool USART::FrameError()
{
    return *CSRA & 0b00010000; //!= 0
}

//DOR (R)
bool USART::DataOverrunError()
{
    return *CSRA & 0b00001000; //!= 0
}

//PE (R)
bool USART::ParityError()
{
    return *CSRA & 0b00000100; //!= 0
}

//U2X (R/W)
bool USART::DoubleTransmissionSpeedIsEnabled()
{
    return *CSRA & 0b00000010; //!= 0
}
void USART::EnableDoubleTransmissionSpeed()
{
    *CSRA |= 0b00000010;
} 
void USART::DisableDoubleTransmissionSpeed()
{   
    *CSRA &= 0b11111101;
}

//MPCM (R/W)
bool USART::MultiProcessorCommunicationModeIsEnabled()
{
    return *CSRA & 0b00000001;
}
void USART::EnableMultiProcessorCommunicationMode()
{
    *CSRA |= 0b00000001;
}
void USART::DisableMultiProcessorCommunicationMode()
{
    *CSRA &= 0b11111110;
}




//UCSRB//
//RXCIE (R/W)
bool USART::RxCompleteInterruptIsEnabled()
{
    return *CSRB & 0b10000000; //!= 0
}
void USART::EnableRxCompleteInterrupt()
{
   *CSRB |= 0b10000000;
}
void USART::DisableRxCompleteInterrupt()
{
    *CSRB &= 0b01111111;
}

//TXCIE (R/W)
bool USART::TxCompleteInterruptIsEnabled()
{
    return *CSRB & 0b01000000; //!= 0
}
void USART::EnableTxCompleteInterrupt()
{
    *CSRB |= 0b01000000;
}
void USART::DisableTxCompleteInterrupt()
{
    *CSRB &= 0b10111111;
}

//UDRIE (R/W)
bool USART::DataRegisterEmptyInterruptIsEnabled()
{
    return *CSRB & 0b00100000; //!= 0
}
void USART::EnableDataRegisterEmptyInterrupt()
{
    *CSRB |= 0b00100000;
}
void USART::DisableDataRegisterEmptyInterrupt()
{
    *CSRB &= 0b11011111;
}

//RXEN (R/W)
bool USART::RxIsEnabled()
{
    return *CSRB & 0b00010000; //!= 0
}
void USART::EnableRx()
{
    *CSRB |= 0b00010000;    
}
void USART::DisableRx()
{
    *CSRB &= 0b11101111;
}

//TXEN (R/W)
bool USART::TxIsEnabled()
{
    return *CSRB & 0b00001000; //!= 0
}
void USART::EnableTx()
{
    *CSRB |= 0b00001000;
}
void USART::DisableTx()
{
    *CSRB &= 0b11110111;
}

//UCSZ2 (R/W) (See FrameSize funcs)

//RXB8 (R)
byte USART::GetRxBit9()
{
    return (*CSRB & 0b00000010) >> 1;
}
byte USART::GetTxBit9()
{
    return *CSRB & 0b00000001;
}
void USART::SetTxBit9()
{
    *CSRB |= 0b00000001;
}
void USART::ClearTxBit9()
{
    *CSRB &= 0b11111110;
}



//UCSRC//
//UMSEL (R/W)
USART::Mode USART::GetMode()
{
    return (Mode)((*CSRC & 0b11000000) >> 6);
}
void USART::SetMode(Mode mode)
{
    *CSRC &= 0b00111111; //Clear
    *CSRC |= mode << 6; //Set
}

//UPM (R/W)
USART::Parity USART::GetParity()
{
    return (Parity)((*CSRC & 0b00110000) >> 4);
}
void USART::SetParity(Parity mode)
{
    *CSRC &= 0b11001111; //Clear
    *CSRC |= mode << 4; //Set
}

//USBS (R/W)
USART::StopBits USART::GetStopBits()
{
    return (StopBits)((*CSRC & 0b00001000) >> 3);
}
void USART::SetStopBits(StopBits size)
{
    *CSRC &= 0b11110111; //Clear
    *CSRC |= size << 3; //Set
}

//UCSZ (R/W)
USART::FrameSize USART::GetFrameSize()
{
    return (FrameSize)((*CSRB & 0b00000100) + ((*CSRC & 0b00000110) >> 1));
}
void USART::SetFrameSize(FrameSize size) //size can be 5-9 bits
{
    *CSRC &= 0b11111001; //Clear UCSZ 0 & 1
    *CSRB &= 0b11111011; //Clear UCSZ 2
    
    *CSRC |= size << 1; //Set UCSZ 0 & 1
    *CSRC |= size; //Set UCSZ 2
}

//UCPOL
USART::ClockPolarity USART::GetClockPolarity()
{
    return (ClockPolarity)(*CSRC & 0b00000001);
}
void USART::SetClockPolarity(ClockPolarity polarity)
{
    *CSRC &= 0b11111110; //Clear
    *CSRC |= polarity; //Set
}


//Core Funcs
void USART::SetBaudRate(unsigned long baud_rate)
{
    unsigned short val = 0;
    
    if(GetMode() == SYNC) //SYNC
        val = F_CPU/(2UL*baud_rate)-1;
    else if(DoubleTransmissionSpeedIsEnabled()) //Double ASYNC
        val = F_CPU/(8UL*baud_rate)-1;
    else //ASYNC
        val = F_CPU/(16UL*baud_rate)-1;
    
    *BRRH = (val >> 8) & 0b00001111; //Set URBBH
    *BRRL = val; //Set UBRRL
}
void USART::Write(char data)
{
    while(!DataRegisterEmpty()){}
    *DR = data;
}
void USART::Write(char* buffer)
{
    for(byte i = 0; buffer[i] != 0; i++)
    {
        Write(buffer[i]);
    } 
}
void USART::Writeln(char* buffer)
{
    Write(buffer);
    Write('\n');
}
byte USART::Read()
{
    return *DR;
}
void USART::begin(unsigned long baud_rate)
{
    SetFrameSize(EIGHT);
    SetStopBits(ONE);
    SetParity(DISABLED); 
    SetBaudRate(baud_rate);
    EnableTx();
    EnableRx();
}
