/*
 * Tomasz Kowalczyk
 * Lukasz Zawistowicz
 */

#include "utils.h"

#define timeout 5
#define maxTime 1000

void turnOff(int nr)
{
    PORTA |= 1 << (7 - nr);
}

void turnOn(int nr)
{
    PORTA &= ~(1 << (7 - nr));
}

void displayNumber(int number)
{
    static const int numbers[10] =
        {
            0b00000011, //0
            0b10011111, //1
            0b00100101, //2
            0b00001101, //3
            0b10011001, //4
            0b01001001, //5
            0b01000001, //6
            0b00011111, //7
            0b00000001, //8
            0b00001001, //9
        };
    PORTA = numbers[number];
}

void switchSegment(int number)
{
    static const int segments[4] =
        {
            0b11111110, //0
            0b11111101, //1
            0b11111011, //2
            0b11110111, //3
        };
    PORTB = segments[number];
}

int main(void)
{
    DDRA = 0xff;
    DDRB = 0xff;

    //PORTB = 0b11111110;

    int value[4] =
        {
            0,0,0,0
        };

    int timePast = 0;

    int number = 0;
    while(1)
    {
        if(number > 9)
        {
            number = 0;
        }
        for(int i = 0; i < 4; ++i)
        {
            switchSegment(i);
            displayNumber(number);
            _delay_ms(timeout);
            timePast += timeout;
        }
        if(timePast > maxTime)
        {
            timePast = 0;
            ++number;
        }
    }
}
