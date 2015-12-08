
// Tomasz Kowalczyk
// Łukasz Zawistowicz

#include <avr/io.h>             // dołączenie głównego systemowego  pliku nagłówkowego
#include <avr/interrupt.h>
#include <util/delay.h>
#include <math.h>
#include <stdbool.h>

int timer = 0;
bool numberOfSegmentToUse = 0;
int numberToDisplay[2] = {0, 0};

void wasteSomeCpuCycle()
{
    for(int i = 0; i < 10; ++i);
}

int naiwny_log(int liczba)
{
    switch(liczba){
      case 8:
          return 3;

      case 4:
          return 2;

      case 2:
          return 1;

      default:
          return 0;
    }
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
    static const int numberToDisplay[4] =
        {
            0b11111110, //0
            0b11111101, //1
            0b11111011, //2
            0b11110111, //3
        };
    PORTB = numberToDisplay[number];
}

int getVerticalPositionOfPressedButton()
{
    DDRD = 0xF0;
    PORTD = 0x0F;
    wasteSomeCpuCycle();
    return naiwny_log(15 - PIND);
}

int getHorizontalPositionOfPressedButton()
{
    DDRD = 0x0F;
    PORTD = 0xF0;
    wasteSomeCpuCycle();
    return naiwny_log(15 - (PIND/16));
}

void calculateNumberOfPressedButton()
{
    if(timer < 400)
    {
        return;
    }
    int number = getVerticalPositionOfPressedButton() * 4 + getHorizontalPositionOfPressedButton();
    numberToDisplay[1] = number/10;
    if(number >= 10)
    {
        number -= 10;
    }
    numberToDisplay[0] = number;
    timer=0;
}

void displayNumberOfPressedButton()
{
    switchSegment(numberOfSegmentToUse);
    displayNumber(numberToDisplay[numberOfSegmentToUse]);
    numberOfSegmentToUse = !numberOfSegmentToUse;
}

ISR(TIMER0_COMP_vect)
{
    calculateNumberOfPressedButton();
    displayNumberOfPressedButton();
    timer++;
}

void config()
{
    OCR0 = 250;
    TCCR0 |= (0<<WGM00) | (1<< WGM01);
    TCCR0 |= (1<<CS00) | (1<< CS01) | (0<<CS02);
    TIMSK |= (1<<OCIE0);
    sei();
}

int main(void) {

    DDRA = 0xFF;
    PORTA = 0xFF;

    DDRB = 0xFF;
    PORTB = 0x0F;

    config();
    while(1)
    {
    }
}
