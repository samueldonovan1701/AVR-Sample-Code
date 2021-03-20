#ifndef SAMS_SERIAL
#define SAMS_SERIAL

#include <avr/io.h>
typedef unsigned char byte;
typedef volatile byte reg;

class USART
{
public:
    reg* BRRL; //Baud Rate Register Lower//
    reg* BRRH; //Baud Rate Register Higher//
    reg* CSRA; //Control & Status Register A// [RxC,   TxC,   UDRE,  FE,   DOR,   PE,    U2X,   MPCM]
    reg* CSRB; //Control & Status Register B// [RXCIE, TXCIE, UDRIE, RXEN, TXEN,  UCSZ2, RXB8,  TXB8]
    reg* CSRC; //Control & Status Register C// [URSEL, UMSEL, UPM1,  UPM0, USBS,  UCSZ1, UCSZ0, UCPOL]
    reg* DR;   //Data Register//               [UDR[7:0]]

//Class
    USART(reg* UBRRL, reg* UBRRH, reg* UCSRA, reg* UCSRB, reg* UCSRC, reg* UDR);

//CSRA//
    bool RxComplete(); //RxC (R)
    bool TxComplete();  //TxC (R)
    void SetTxComplete(); //TxC (W 1)
    void ClearTxComplete(); //TxC (W 0)
    bool DataRegisterEmpty(); //UDRE (R)
    bool FrameError(); //FE (R)
    bool DataOverrunError(); //DOR (R)
    bool ParityError(); //PE (R)
    bool DoubleTransmissionSpeedIsEnabled(); //U2X (R)
    void EnableDoubleTransmissionSpeed(); //U2X (W 1)
    void DisableDoubleTransmissionSpeed(); //U2X (W 0)
    bool MultiProcessorCommunicationModeIsEnabled(); //MPCM (R)
    void EnableMultiProcessorCommunicationMode(); //MPCM (W 1)
    void DisableMultiProcessorCommunicationMode(); //MPCM (W 0)
    
//UCSRB//
    bool RxCompleteInterruptIsEnabled(); //RXCIE (R)
    void EnableRxCompleteInterrupt(); //RXCIE (W 1)
    void DisableRxCompleteInterrupt(); //RXCIE (W 0)
    bool TxCompleteInterruptIsEnabled(); //TXCIE (R)
    void EnableTxCompleteInterrupt(); //TXCIE (W 1)
    void DisableTxCompleteInterrupt(); //TXCIE (W 0)
    bool DataRegisterEmptyInterruptIsEnabled(); //UDRIE (R)
    void EnableDataRegisterEmptyInterrupt(); //UDRIE (W 1)
    void DisableDataRegisterEmptyInterrupt(); //UDRIE (W 0)
    bool RxIsEnabled(); //RXEN (R)
    void EnableRx(); //RXEN (W 1)
    void DisableRx(); //RXEN (W 0)
    bool TxIsEnabled(); //TXEN (R)
    void EnableTx(); //TXEN (W 1)
    void DisableTx(); //TXEN (W 0)
    byte GetRxBit9(); //RXB8 (R)
    byte GetTxBit9(); //TXB8 (R)
    void SetTxBit9(); //TXB8 (W 1)
    void ClearTxBit9(); //TXB8 (W 0)
    
//UCSRC//
    enum Mode{
       ASYNC = 0b00,
       SYNC = 0b01,
       MSPIM = 0b11  
    };
    Mode GetMode(); //UMSEL (R)
    void SetMode(Mode mode=ASYNC); //UMSEL (W)

    enum Parity {
        DISABLED = 0b00,
        RESERVED = 0b01,
        EVEN = 0b10,
        ODD = 0b11
    };
    Parity GetParity(); //UPM (R)
    void SetParity(Parity mode=DISABLED); //UPM (W)

    enum StopBits{
        ONE = 0,
        TWO = 1
    };
    StopBits GetStopBits(); //USBS (R)
    void SetStopBits(StopBits size=ONE); //USBS (W)

    enum FrameSize {
        FIVE = 0b000,
        SIX = 0b001,
        SEVEN = 0b101,
        EIGHT = 0b011,
        NINE = 0b111
    };
    FrameSize GetFrameSize(); //UCSZ (R)
    void SetFrameSize(FrameSize size = EIGHT); //UCSZ (W)

    enum ClockPolarity{
        RISING_EDGE = 0,
        RALLING_EDGE = 1
    };
    ClockPolarity GetClockPolarity();
    void SetClockPolarity(ClockPolarity polarity=RISING_EDGE);
    
//Core Funcs
    void SetBaudRate(unsigned long BAUD_RATE);
    void Write(char c);
    void Write(char* buffer);
    void Writeln(char* buffer);
    byte Read();
    void begin(unsigned long BAUD_RATE);
};

//USART Definitions//
extern USART USART0;
extern USART USART1;
extern USART USART2;
extern USART USART3;
#endif
