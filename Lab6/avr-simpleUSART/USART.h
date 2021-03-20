#ifndef SIMPLE_USART
#define SIMPLE_USART

#include <avr/io.h>
typedef uint8_t byte;
typedef volatile uint8_t reg;

class USART
{
private:
    reg* BRRL; //Baud Rate Register Lower//
    reg* BRRH; //Baud Rate Register Higher//
    reg* CSRA; //Control & Status Register A// [RxC,   TxC,   UDRE,  FE,   DOR,   PE,    U2X,   MPCM]
    reg* CSRB; //Control & Status Register B// [RXCIE, TXCIE, UDRIE, RXEN, TXEN,  UCSZ2, RXB8,  TXB8]
    reg* CSRC; //Control & Status Register C// [URSEL, UMSEL, UPM1,  UPM0, USBS,  UCSZ1, UCSZ0, UCPOL]
    reg* DR;   //Data Register//               [UDR[7:0]]

public:
//Class
    USART(reg* UBRRL, reg* UBRRH, reg* UCSRA, reg* UCSRB, reg* UCSRC, reg* UDR)
    {
        BRRL = UBRRL;
        BRRH = UBRRH;
        CSRA = UCSRA;
        CSRB = UCSRB;
        CSRC = UCSRC;
        DR = UDR;
    }
    #define USART(N) USART(&UBRR##N##L, &UBRR##N##H, &UCSR##N##A, &UCSR##N##B, &UCSR##N##C, &UDR##N);

//UCSRA//
    //RxC (R)
    bool RxComplete()
    {
        return *CSRA & 0b10000000; // != 0
    }

    //TxC (W/R)
    bool TxComplete()
    {
        return *CSRA & 0b01000000; // != 0
    }
    void SetTxComplete()
    {
        *CSRA |= 0b01000000;
    }
    void ClearTxComplete()
    {
        *CSRA &= 0b10111111;
    }

    //UDRE (R)
    bool DataRegisterEmpty()
    {
        return *CSRA & 0b00100000; //!= 0
    }

    //FE (R)
    bool FrameError()
    {
        return *CSRA & 0b00010000; //!= 0
    }

    //DOR (R)
    bool DataOverrunError()
    {
        return *CSRA & 0b00001000; //!= 0
    }

    //PE (R)
    bool ParityError()
    {
        return *CSRA & 0b00000100; //!= 0
    }

    //U2X (R/W)
    bool DoubleTransmissionSpeedIsEnabled()
    {
        return *CSRA & 0b00000010; //!= 0
    }
    void EnableDoubleTransmissionSpeed()
    {
        *CSRA |= 0b00000010;
    } 
    void DisableDoubleTransmissionSpeed()
    {   
        *CSRA &= 0b11111101;
    }

    //MPCM (R/W)
    bool MultiProcessorCommunicationModeIsEnabled()
    {
        return *CSRA & 0b00000001;
    }
    void EnableMultiProcessorCommunicationMode()
    {
        *CSRA |= 0b00000001;
    }
    void DisableMultiProcessorCommunicationMode()
    {
        *CSRA &= 0b11111110;
    }




//UCSRB//
    //RXCIE (R/W)
    bool RxCompleteInterruptIsEnabled()
    {
        return *CSRB & 0b10000000; //!= 0
    }
    void EnableRxCompleteInterrupt()
    {
       *CSRB |= 0b10000000;
    }
    void DisableRxCompleteInterrupt()
    {
        *CSRB &= 0b01111111;
    }

    //TXCIE (R/W)
    bool TxCompleteInterruptIsEnabled()
    {
        return *CSRB & 0b01000000; //!= 0
    }
    void EnableTxCompleteInterrupt()
    {
        *CSRB |= 0b01000000;
    }
    void DisableTxCompleteInterrupt()
    {
        *CSRB &= 0b10111111;
    }

    //UDRIE (R/W)
    bool DataRegisterEmptyInterruptIsEnabled()
    {
        return *CSRB & 0b00100000; //!= 0
    }
    void EnableDataRegisterEmptyInterrupt()
    {
        *CSRB |= 0b00100000;
    }
    void DisableDataRegisterEmptyInterrupt()
    {
        *CSRB &= 0b11011111;
    }

    //RXEN (R/W)
    bool RxIsEnabled()
    {
        return *CSRB & 0b00010000; //!= 0
    }
    void EnableRx()
    {
        *CSRB |= 0b00010000;    
    }
    void DisableRx()
    {
        *CSRB &= 0b11101111;
    }

    //TXEN (R/W)
    bool TxIsEnabled()
    {
        return *CSRB & 0b00001000; //!= 0
    }
    void EnableTx()
    {
        *CSRB |= 0b00001000;
    }
    void DisableTx()
    {
        *CSRB &= 0b11110111;
    }

    //UCSZ2 (R/W) (See FrameSize funcs)
    //RXB8 (R)
    byte GetRxBit9()
    {
        return (*CSRB & 0b00000010) >> 1;
    }
    byte GetTxBit9()
    {
        return *CSRB & 0b00000001;
    }
    void SetTxBit9()
    {
        *CSRB |= 0b00000001;
    }
    void ClearTxBit9()
    {
        *CSRB &= 0b11111110;
    }

//UCSRC//
    //UMSEL (R/W)
    enum Mode{
       ASYNC = 0b00,
       SYNC = 0b01,
       MSPIM = 0b11  
    };
    Mode GetMode()
    {
        return (Mode)((*CSRC & 0b11000000) >> 6);
    }
    void SetMode(Mode mode)
    {
        *CSRC &= 0b00111111; //Clear
        *CSRC |= mode << 6; //Set
    }

    //UPM (R/W)
    enum Parity {
        DISABLED = 0b00,
        RESERVED = 0b01,
        EVEN = 0b10,
        ODD = 0b11
    };
    Parity GetParity()
    {
        return (Parity)((*CSRC & 0b00110000) >> 4);
    }
    void SetParity(Parity mode)
    {
        *CSRC &= 0b11001111; //Clear
        *CSRC |= mode << 4; //Set
    }

    //USBS (R/W)
    enum StopBits{
        ONE = 0,
        TWO = 1
    };
    StopBits GetStopBits()
    {
        return (StopBits)((*CSRC & 0b00001000) >> 3);
    }
    void SetStopBits(StopBits size)
    {
        *CSRC &= 0b11110111; //Clear
        *CSRC |= size << 3; //Set
    }

    //UCSZ (R/W)
    enum FrameSize {
        FIVE = 0b000,
        SIX = 0b001,
        SEVEN = 0b101,
        EIGHT = 0b011,
        NINE = 0b111
    };
    FrameSize GetFrameSize()
    {
        return (FrameSize)((*CSRB & 0b00000100) + ((*CSRC & 0b00000110) >> 1));
    }
    void SetFrameSize(FrameSize size) //size can be 5-9 bits
    {
        *CSRC &= 0b11111001; //Clear UCSZ 0 & 1
        *CSRB &= 0b11111011; //Clear UCSZ 2
        
        *CSRC |= size << 1; //Set UCSZ 0 & 1
        *CSRC |= size; //Set UCSZ 2
    }

    //UCPOL
    enum ClockPolarity{
        RISING_EDGE = 0,
        FALLING_EDGE = 1
    };
    ClockPolarity GetClockPolarity()
    {
        return (ClockPolarity)(*CSRC & 0b00000001);
    }
    void SetClockPolarity(ClockPolarity polarity)
    {
        *CSRC &= 0b11111110; //Clear
        *CSRC |= polarity; //Set
    }


//Core Funcs
    void SetBaudRate(unsigned long baud_rate)
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
    void Write(char data)
    {
        while(!DataRegisterEmpty()){}
        *DR = data;
    }
    void Write(char* buffer)
    {
        for(byte i = 0; buffer[i] != 0; i++)
        {
            Write(buffer[i]);
        } 
    }
    void Write(int i, int base=10)
    {
        char buf[20];
        itoa(i, buf, base);
        Write(buf);
    }
    void Writeln(char* buffer)
    {
        Write(buffer);
        Write('\n');
    }
    void Writeln(int i, int base=10)
    {
        Write(i, base);
        Write('\n');
    }
    byte Read()
    {
        return *DR;
    }
    void begin(unsigned long baud_rate)
    {
        SetFrameSize(EIGHT);
        SetStopBits(ONE);
        SetParity(DISABLED); 
        SetBaudRate(baud_rate);
        EnableTx();
        EnableRx();
    }
};

//USART Definitions//
USART USART0 = USART(0);
USART USART1 = USART(1);
USART USART2 = USART(2);
USART USART3 = USART(3);

#endif
