# avr-usart
Simple Serial (USART) communication for Arduino

Written for and tested on a ATMEGA2560

## Usage
To use the library, clone or download it to your project directory and
```c
#include "avr-USART/USART.h"
```

### Pre-definitions
USART0 through USART3 are conditionally defined in `USART.h`. It is recommended to use these rather than instantiating a new USART object. 

If you wish to access other USART ports, you will have to instantiate them yourself.

`USART0` is usually tied to the board's USB port

### Constructor
If you would like to instantiate a new isntance of a specific USART port, this is available through the macro
```c
USART x = USART(N);
```
Where `N` is the integer USART port you desire

Attempting to instntiate a USART port that does not exist will cause a compile-time error.

## Core Functions
### begin(baud_rate)
Sets baud rate to that provided, as well as the following:
- Frame Size = 8
- Stop Bits = 1
- Parity = Disabled
- Tx = Enabled
- Rx = Enabled

### Read()
Reads the current character in the USART's data register

### Write(char)
Writes a character to the USART's data register. Blocked until the data register is empty.

### Write(char\*)
Sequentially writes a cstring to the data register (must be null terminated)

### SetBaudRate(ulong)
Sets the USART port's baud rate

## UCSRA Functions
### RxComplete()
Returns 1 if the `RxC` flag is set, 0 otherwise

### TxComplete()
Returns 1 if the `TxC` flag is set, 0 otherwise

### SetTxCompelte()
Sets the `TxC` flag

### ClearTxCompelte()
Clears the `TxC` flag

### DataRegisterEmpty()
Returns 1 if the `UDRE` flag is set, 0 otherwise

### Frane Error()
Returns 1 if the `FE` flag is set, 0 otherwise

### DataOverrunError()
Returns 1 if the `DOR` flag is set, 0 otherwise

### ParityError()
Returns 1 if the `PE` flag is set, 0 otherwise

### DoubleTransmissionSpeedIsEnabled()
Returns 1 if the `U2X` flag is set, 0 otherwise

### EnabledDoubleTransmissionSpeed()
Sets the `U2X` flag

### DisabledDoubleTransmissionSpeed()
Clears the `U2X` flag

### MultiProcessorCommunicationModeIsEnabled()
Returns 1 if the `MPCM` flag is set, 0 otherwise

### EnableMultiProcessorCommunicationMode()
Sets the `MPCM` flag

### DisableMultiProcessorCommunicationMode()
Clears the `MPCM` flag

## UCSRB Functions
### RxCompleteInterruptIsEnabled()
Returns 1 if the `RXCIE` flag is set, 0 otherwise

### EnableRxCompleteInterrupt()
Sets the `RXCIE` flag

### DisableRxCompleteInterrupt()
Clears the `RXCIE` flag

### TxCompleteInterruptIsEnabled()
Returns 1 if the `TXCIE` flag is set, 0 otherwise

### EnableTxCompleteInterrupt()
Sets the `TXCIE` flag

### DisableTxCompleteInterrupt()
Clears the `TXCIE` flag

### DataRegisterEmptyInterruptIsEnabled()
Returns 1 if the `UDRIE` flag is set, 0 otherwise

### EnableDataRegisterEmptyInterrupt()
Sets the `UDRIE` flag

### DisableDataRegisterEmptyInterrupt()
Clears the `UDRIE` flag

### RxIsEnabled()
Returns 1 if the `RXEN` flag is set, 0 otherwise

### EnableRx()
Sets the `RXEN` flag

### DisableRx()
Clears the `RXEN` flag

### TxIsEnabled()
Returns 1 if the `TXEN` flag is set, 0 otherwise

### EnableTx()
Sets the `TXEN` flag

### DisableTx()
Clears the `TXEN` flag

### GetRxBit9()
Returns 1 if the `RXB8` is set, 0 otherwise

### GetTxBit9()
Returns 1 if the `TXB8` is set, 0 otherwise

### SetTxBit9()
Sets `TXB8`

### ClearTxBit9()
Clears `TXB8`

## UCSRC Functions
### Modes (USART::Mode)
- 0b00 : ASYNC
- 0b01 : SYNC
- 0b11 : MSPIM (Master SPI Mode)

### GetMode()
Returns which mode of operation the USART port is in

### SetMode(USART::Mode)
Sets the USART port's mode of operation

### Parity (USART::Parity)
- 0b00 : DISABLED
- 0b01 : RESERVED
- 0b10 : EVEN
- 0b11 : ODD

### GetParity()
Returns which parity mode the USART port is in

### SetParity(USART::Parity)
Sets the USART port's parity mode

### Stop Bits (USART::StopBits)
- 0b0 : ONE
- 0b1 : TWO

### GetStopBits()
Returns how many stop bits the USART port is using for communication

### SetStopBits(USART::StopBits)
Sets how many stop bits the USART port will use for communication

### Frame Size (USART::FrameSize)
- 0b000 : FIVE
- 0b001 : SIX
- 0b101 : SEVEN
- 0b011 : EIGHT
- 0b111 : NINE

### GetFrameSize()
Returns the frame size the USART port is using for communication

### SetFrameSize(USART::FrameSize)
Sets the frame size the USART port will use for communication

### Clock Polarity (USART::ClockPolarity)
- 0 : RISING_EDGE
- 1 : FALLING_EDGE

### GetClockPolarity()
Returns the clock polarity mode the USART port is using for communication

### SetClockPolarity(USART::ClockPolarity)
Sets the clock polarity mode the USART port will use for communication

## Supported Boards
- ATMEGA2560

(may still work on others)

# Limitations
- Need some familiarity with USART