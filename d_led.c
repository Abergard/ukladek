#include <avr/io.h>         // do��czenie g��wnego systemowego  pliku nag��wkowego
#include <avr/interrupt.h>  // do��czenie pl. nag��wkowego potrzebnego do obs�. przerwa�
#include <avr/pgmspace.h>   // do��czenie pl. nag��wkowego potrzebnego do odczytu
                            // danych zawartych w pami�ci programu FLASH

#include "d_led.h"          // do��czenie naszego pliku nag��wkowego
                            // w nim znajduj� si� potrzebne tu m.in. definicje preprocesora

#include "game_logic/game.h"

// definicje zmiennych globalnych przechowuj�cych cyfry do wy�wietlania
// volatile � poniewa� b�d� wykorzystywane do odczytu i zapisu zar�wno w przerwaniu i programie
// g��wnym. Trzeba wi�c wy��czy� optymalizacj� dost�pu do nich. (zmienne ulotne)
volatile uint8_t cy1;
volatile uint8_t cy2;
volatile uint8_t cy3;
volatile uint8_t cy4;


// definicja tablicy zawieraj�cej definicje bitowe cyfr LED
const uint8_t cyfry[15] PROGMEM =
{
    0xC0,   // 0
    0xF9,   // 1   0b10011111
    0xA4,   // 2
    0xB0,   // 3
    0x99,   // 4   0b10011001
    0x92,   // 5
    0x82,   // 6
    0xD8,   // 7
    0x80,   // 8
    0x90,   // 9   0b00001001
    0xFF    // NIC (puste miejsce)
};



// ****** definicja funkcji inicjalizuj�cej prac� z wy�wietlaczem multipleksowanym
void d_led_init(void)
{
    LED_DATA_DIR = 0xFF;                    // wszystkie piny portu C jako WYJ�CIA(katody)
    LED_DATA = 0xFF;                        // wygaszenie wszystkich katod � stan wysoki
    ANODY_DIR |= CA1 | CA2 | CA3 | CA4;     // 4 piny portu A jako WYJ�CIA (anody wy�wietlaczy)
    ANODY_PORT |= CA1 | CA2 | CA3  | CA4;   // wygaszenie wszystkich wy�wietlaczy - anody

    // ustawienie TIMER0
    TCCR0 |= (1<<WGM01);                    // tryb CTC Mode2 Nota PDF
    TCCR0 |= (1<<CS02)|(1<<CS00);           // preskaler = 1024
    OCR0 = 38;                              // dodatkowy podzia� przez 39 (rej. przepe�nienia)
    TIMSK |= (1<<OCIE0);                    // zezwolenie na przerwanie CompareMatch
}

unsigned time;

// ================= PROCEDURA OBS�UGI PRZERWANIA � COMPARE MATCH
ISR(TIMER0_COMP_vect)
{
	static int licz = 0;

    static uint8_t licznik=1;                                       // zmienna do prze��czania kolejno anod wy�wietlacza

	licz++;
 	if (!(licz % 400))
 	{

 	     ++game.time;
 	}


     time = getGameTime();
     cy3 = time / 1000;
     time -= cy3*1000;
     cy4 = time / 100;
     time -= cy4*100;
     cy1 = time / 10;
     time -= cy1*10;
     cy2 = time;

    ANODY_PORT = (ANODY_PORT | MASKA_ANODY);                        // wygaszenie wszystkich wy�wietlaczy

    if(licznik==1)      LED_DATA = pgm_read_byte( &cyfry[cy1] );    // gdy zapalony wy�w.1 podaj stan zmiennej c1
    else if(licznik==2) LED_DATA = pgm_read_byte( &cyfry[cy2] );    // gdy zapalony wy�w.2 podaj stan zmiennej c2
    else if(licznik==4) LED_DATA = pgm_read_byte( &cyfry[cy3] );    // gdy zapalony wy�w.3 podaj stan zmiennej c3
    else if(licznik==8) LED_DATA = pgm_read_byte( &cyfry[cy4] );    // gdy zapalony wy�w.4 podaj stan zmiennej c4

    ANODY_PORT = (ANODY_PORT & ~MASKA_ANODY) | (~licznik & MASKA_ANODY);            // cykliczne prze��czanie kolejnej anody w ka�dym przerwaniu

    // operacje cyklicznego przesuwania bitu zapalaj�cego anody w zmiennej licznik
    licznik <<= 1;                  // przesuni�cie zawarto�ci bit�w licznika o 1 w lewo
    if(licznik>8)
    {
    	licznik = 1;      // je�li licznik wi�kszy ni� 8 to ustaw na 1
    }
//
//    if(slowerPls>1000000)
//    {
//    	slowerPls = 0;
//    	++game.time;
//    }
}
