/*
 * Tomasz Kowalczyk
 * Lukasz Zawistowicz
 */

#include "utils.h"

void wait(uint32_t czas)
{
    for(uint32_t i = 0; i < czas; i++)
    {
        _delay_us(1);
    }
}

void setAll_PortA()
{
    PORTA = 0xff;
}

void setAll_PortB()
{
    PORTB = 0xff;
}

void setAll_PortC()
{
    PORTC = 0xff;
}

void setAll_PortD()
{
    PORTD = 0xff;
}

void unsetAll_PortA()
{
    PORTA = 0x00;
}

void unsetAll_PortB()
{
    PORTB = 0x00
}

void unsetAll_PortC()
{
    PORTC = 0x00
}

void unsetAll_PortD()
{
    PORTD = 0x00
}

void setAt_PortA(uint8_t position)
{
    PORTA |= (1 << position);
}

void setAt_PortB(uint8_t position)
{
    PORTB |= (1 << position);
}

void setAt_PortC(uint8_t position)
{
    PORTC |= (1 << position);
}

void setAt_PortD(uint8_t position)
{
    PORTD |= (1 << position);
}

void unsetAt_PortA(uint8_t position)
{
    PORTA &= ~(1 << position);
}

void unsetAt_PortB(uint8_t position)
{
    PORTB &= ~(1 << position);
}

void unsetAt_PortC(uint8_t position)
{
    PORTC &= ~(1 << position);
}

void unsetAt_PortD(uint8_t position)
{
    PORTD &= ~(1 << position);
}

bool isSetAt_PortA(uint8_t position)
{
    return (PORTA & (1 << position));
}

bool isSetAt_PortB(uint8_t position)
{
    return (PORTB & (1 << position));
}

bool isSetAt_PortC(uint8_t position)
{
    return (PORTC & (1 << position));
}

bool isSetAt_PortD(uint8_t position)
{
    return (PORTD & (1 << position));
}

bool isSetAt_PinA(uint8_t position)
{
    return (PINA & (1 << position));
}

bool isSetAt_PinB(uint8_t position)
{
    return (PINB & (1 << position));
}

bool isSetAt_PinC(uint8_t position)
{
    return (PINC & (1 << position));
}

bool isSetAt_PinD(uint8_t position)
{
    return (PIND & (1 << position));
}

void setInputAll_PortA()
{
    DDRA = 0x00;
}

void setInputAll_PortB()
{
    DDRB = 0x00;
}

void setInputAll_PortC()
{
    DDRC = 0x00;
}

void setInputAll_PortD();
{
    DDRD = 0x00;
}

void setOutputAll_PortA()
{
    DDRA = 0xff;
}

void setOutputAll_PortB()
{
    DDRB = 0xff;
}

void setOutputAll_PortC()
{
    DDRC = 0xff;
}

void setOutputAll_PortD()
{
    DDRD = 0xff;
}

void setInputAt_PortA(uint8_t position)
{
    DDRA &= ~(1 << position);
}

void setInputAt_PortB(uint8_t position)
{
    DDRB &= ~(1 << position);
}

void setInputAt_PortC(uint8_t position)
{
    DDRC &= ~(1 << position);
}

void setInputAt_PortD(uint8_t position)
{
    DDRD &= ~(1 << position);
}

void setOutputAt_PortA(uint8_t position)
{
    DDRA |= (1 << position);
}

void setOutputAt_PortB(uint8_t position)
{
    DDRB |= (1 << position);
}

void setOutputAt_PortC(uint8_t position)
{
    DDRC |= (1 << position);
}

void setOutputAt_PortD(uint8_t position)
{
    DDRD |= (1 << position);
}
