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

#define LED_PIN (1<<PD0)                                                // definicja pinu do którego pod³aczamy diode LED
#define LED_ON PORTD &= ~LED_PIN                                        // makrodefinicja - zalaczenia diody
#define LED_OFF PORTD |= LED_PIN                                        // makrodefinicja - wylaczenie diody
#define LED_TOG PORTD ^= LED_PIN                                        // makrodefinicja - zmiana stanu diody
#define K1 (1<<PD7)
#define K2 (1<<PD6)
#define K3 (1<<PD5)
#define K4 (1<<PD4)

uint8_t isPressedLeft = 0;
uint8_t isPressedRight = 0;
uint8_t isPressedEnter = 0;
uint8_t isPressedBack = 0;

uint8_t pressed_button(uint8_t key)
{
    if (!(PIND & key))
    {                                                              // czas drgañ styków
        if(!(PIND & key)) return 1;
    }
    return 0;
}


void led_win()
{
    DDRD |= LED_PIN;
    int i = 0;
    while(i < 10)
    {
        LED_TOG;
        _delay_ms(500);
        i++;
    }
    LED_OFF;
}

void led_end()
{
    DDRD |= LED_PIN;
    int i = 0;
    while(i < 10)
    {
        LED_TOG;
        _delay_ms(500);
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
    //lcd_blink_on();
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
            game.up();
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
            game.down();
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
            game.enter();
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
            game.back();
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
    _delay_ms(80);
}

void printCursorOnLcd()
{
    lcd_locate(1, game.cursorPosition);
}

void display()
{
    if(game.needReDraw)
    {
        game.needReDraw = 0;
        printLcdInFirstRow(getFirstLineToDisplay());
        printLcdInSecondRow(getSecondLineToDisplay());
    }
    if(game.isEnd)
    {
    	game.isEnd = 0;
        if(game.menuState == GAMEEND_WIN)
        {
        	led_win();
        }
        else if(game.menuState == GAMEEND_LOSER)
        {
        	led_end();
        }
    }
    //printCursorOnLcd();
}

void initializeTimer()
{
    // ****** inicjalizacja *********
    d_led_init();           // inicjalizacja wyswietlacza multipleksowanego
    sei();                  // w³¹czenie globalnego zezwolenia na przerwania
}

void updateTimer()
{
    unsigned time = getGameTime();

    cy3 = time / 1000;
    time -= cy3*1000;
    cy4 = time / 100;
    time -= cy4*100;
    cy1 = time / 10;
    time -= cy1*10;
    cy2 = time;

    _delay_ms(430);
}

int main(void)
{
    initializeLcd();

    DDRD &= ~(K1 | K2 | K3 | K4);    // Piny klawiszy - wejscia
    PORTD |= K1 | K2 | K3 | K4;      // Podciagniecie Pinów pod VCC

    initializeTimer();
    gameInit(GAMEMENU_GAMENAME);

    while(1)
    {
        updateGame();
        updateKeyboard();
        //updateTimer();
        display();
    }
    return 0;
}
