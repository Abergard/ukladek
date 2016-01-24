/*
 * Definicje:
 * RS, RW, E -> linie sterujace
 * D0-D7     -> linie danych wyœwietlacza
 * Praca w trybie 4 bitowym D7-D4
 * Wyœwietlacz ma 2 rodzaje pamieci:
 * CGRAM- pamiec w³asnych znaków(8)
 * DDRAM- Kody ASCII
 */

// Definicje:
// Atmegas32 posiada dwa Timery 8 i 16 bitów
// Preskaler - wew dzielnik czestotliwosci taktowania dostarczanej do taktowania timera
// Tryb pracy Timer0 ustawaimy na CTC -> licznik Timer0 w trakcie zliczania bedzie porównywany z wartoscia rejestru OCR0 (Compare Match), je¿eli równe to przerwanie
// OCR0 8 bitów czyli zakres 0-255   OCR0 = (8000000Hz/1024preskaler/200Hz)-1 =38.06    przerwania co 200Hz     38 jest w zbiorze 0-255


#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>
#include "LCD/lcd44780.h"
#include <util/delay.h>
#include "d_led.h"              // do³¹czenie naszego pliku nag³ówkowego (obs³uga LED)
#include <avr/interrupt.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game_logic/game.h"
#include "game_logic/gameinit.h"
#include "game_logic/gamesettings.h"

static Game game =
{
    .up = &noAction,
    .down = &noAction,
    .back = &noAction,
    .enter = &noAction,
    .updateState = &noAction,
    .time = 0,
    .wordId = 0,
    .needReDraw = 0,
    .cursorPosition = 0,
    .word = "                "
};


#define LED_PIN (1<<PD0)                                                // definicja pinu do którego pod³aczamy diode LED
#define LED_ON PORTD &= ~LED_PIN                                        // makrodefinicja - zalaczenia diody
#define LED_OFF PORTD |= LED_PIN                                        // makrodefinicja - wylaczenie diody
#define LED_TOG PORTD ^= LED_PIN                                        // makrodefinicja - zmiana stanu diody
#define K1 (1<<PD7)
#define K2 (1<<PD6)
#define K3 (1<<PD5)
#define K4 (1<<PD4)

short int posX = 0;
short int poxY = 0;

uint8_t isPressedLeft = 0;
uint8_t isPressedRight = 0;
uint8_t isPressedEnter = 0;
uint8_t isPressedBack = 0;
uint8_t d1,d2,d3,d4;
uint8_t znak_buzka[] = {14,17,27,17,17,21,17,14}; // wzór znaku buzki w pamiêci RAM
uint8_t pressed_button(uint8_t key);

uint8_t pressed_button(uint8_t key){
    if (!(PIND & key)){
        _delay_ms(80);                                                                  // czas drgañ styków
        if(!(PIND & key)) return 1;
    }
    return 0;
}


void led_win(){
            DDRD |= LED_PIN;
            int i = 0;
            while(i < 10){
                LED_TOG;
                _delay_ms(2000);
                i++;
            }
            LED_OFF;
    }

void led_end()
{
    DDRD |= LED_PIN;
    int i = 0;
    while(i < 10){
        LED_TOG;
        _delay_ms(2000);
        i++;
    }
    LED_OFF;
}

void initializeLcd()
{
    DDRA |= (1<<PA7);                                                               // ustawiamy kierunek linii podœwietlenia LCD jako WYJŒCIE
    PORTA |= (1<<PA7);                                                              // za³¹czamy podœwietlenie LCD - stan wysoki

    lcd_init();
    lcd_cursor_on();
    lcd_blink_on();
}

void printOnLcdInRow(const char* msg, uint8_t position)
{
    lcd_locate(position,0);
    lcd_str(msg);
}

void printLcdInFirstRow(const char* msg)
{
    printOnLcdInRow(msg, 0);
}

void printLcdInSecondRow(const char* msg)
{
    printOnLcdInRow(msg, 1);
}

void updateLeftKey()
{
    if (pressed_button(K1))
    {
        if(isPressedLeft == 0)
        {
            isPressedLeft = 1;
            game.up(&game);
        }
    }
    else
    {
        isPressedLeft = 0;
    }
}

void updateRightKey()
{
    if (pressed_button(K2))
    {
        if(isPressedRight == 0)
        {
            isPressedRight = 1;
            game.down(&game);
        }
    }
    else
    {
        isPressedRight = 0;
    }
}

void updateEnterKey()
{
    if (pressed_button(K3))
    {
        if(isPressedEnter == 0)
        {
            isPressedEnter = 1;
            game.enter(&game);
        }
    }
    else
    {
        isPressedEnter = 0;
    }
}

void updateBackKey()
{
    if (pressed_button(K4))
    {
        if(isPressedBack == 0)
        {
            isPressedBack = 1;
            game.back(&game);
        }
    }
    else
    {
        isPressedBack = 0;
    }
}

void updateKeyboard()
{
    updateLeftKey();
    updateRightKey();
    updateEnterKey();
    updateBackKey();
}

void printCursorOnLcd()
{
    lcd_locate(1,game.cursorPosition);
}

void display()
{
    if(game.needReDraw)
    {
        game.needReDraw = 0;
        printLcdInFirstRow(getFirstLineToDisplay(&game));
        printLcdInSecondRow(getSecondLineToDisplay(&game));
    }
    printCursorOnLcd();
}

void initializeTimer()
{
    // ****** inicjalizacja *********
    d_led_init();           // inicjalizacja wyswietlacza multipleksowanego
    sei();                  // w³¹czenie globalnego zezwolenia na przerwania
}

void updateTimer()
{
    short time = getGameTimer(&game);
    d1=time/1000;
    if(d1) cy1=d1; else cy1=NIC;
    d2=(time-(d1*1000))/100;
    if(d2) cy2=d2; else cy2=(time>999)?0:NIC;
    d3=(time-(d1*1000)-(d2*100))/10;
    if(d3) cy3=d3; else cy3=(time>99)?0:NIC;
    d4=(time-(d1*1000)-(d2*100)-(d3*10));
    cy4=d4;
    _delay_ms(80);
 //  if(d1 == 1) {
//     led_end();
 //}
}

int main(void)
{
    initializeLcd();

    DDRD &= ~(K1 | K2 | K3 | K4); // Piny klawiszy - wejscia
    PORTD |= K1 | K2 | K3 | K4; // Podciagniecie Pinów pod VCC

    initializeTimer();
    gameInit(&game);

    while(1)
    {
        updateGame(&game);
        updateKeyboard();
        updateTimer();
        display();
    }
    return 0;
}
