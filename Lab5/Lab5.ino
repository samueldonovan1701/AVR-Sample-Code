#include "samsLCD.h"
#include "samsUSART.h"
#include <avr/io.h>
#include <util/delay.h>

//Vars
GPIO D[4] = {
  GPIO(&DDRA, &PORTA, &PINA, 4),
  GPIO(&DDRA, &PORTA, &PINA, 5),
  GPIO(&DDRA, &PORTA, &PINA, 6),
  GPIO(&DDRA, &PORTA, &PINA, 7)
};

GPIO RS = GPIO(&DDRB, &PORTB, &PINB, 0);
GPIO RW = GPIO(&DDRB, &PORTB, &PINB, 2);
GPIO E  = GPIO(&DDRB, &PORTB, &PINB, 1);

LCD lcd = LCD(RS, RW, E, D);


//ISR
volatile byte line = 1;
volatile bool ignoreNext = false;
volatile bool scrollText = false;
ISR(USART0_RX_vect)
{
    char c = USART0.Read();

//Commands
    if(ignoreNext) //Ignore char
    {
        ignoreNext = false;
    }
    else if(c == '\n') // New line
    {
        line = line == 1 ? 2 : 1;
        USART0.Write('\n');
        lcd.SetPos(line, 0);
    }
    else if(c == '`') //Clear
    {
        lcd.Clear();
        USART0.Writeln("Display cleared");
        ignoreNext = true;
    }
    else if(c == '~') //Toggle scrolling
    {
        if(scrollText)
        {
            USART0.Writeln("Text scroll disabled");
            scrollText = false;
        }
        else
        {
            USART0.Writeln("Text scroll enabled");
            scrollText = true;
        }
        ignoreNext = true;
    }
    else //if(isprint(c)) //Printable char
    {
        lcd.Write(c);
        USART0.Write(c);
    }
}


int main(void)
{
    _delay_ms(100);
    
    USART0.EnableRxCompleteInterrupt();
    sei();
    USART0.begin(9600);


    USART0.Writeln("--------------------");
    USART0.Writeln("Welcome to samsLCD!");
    USART0.Writeln("Send something for it to appear on the LCD");
    USART0.Writeln("Use your enter key to switch lines");
    USART0.Writeln("Send '`' to clear the display");
    USART0.Writeln("Send '~' to start/stop text scrolling");
    USART0.Writeln("--------------------");
    lcd.Write("abcdefghi");
    lcd.Write("klmnopqrs", 2);
    while(1)
    {   //Text scrolling
        if(scrollText)
        {
            lcd.ShiftDisplayLeft();
            _delay_ms(1000);
        }
    };
    return 1;
}
