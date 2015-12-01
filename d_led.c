#include <avr/io.h>			// dołączenie głównego systemowego  pliku nagłówkowego
#include <avr/interrupt.h>	// dołączenie pl. nagłówkowego potrzebnego do obsł. przerwań
#include <avr/pgmspace.h>	// dołączenie pl. nagłówkowego potrzebnego do odczytu
							// danych zawartych w pamięci programu FLASH

#include "d_led.h"			// dołączenie naszego pliku nagłówkowego
							// w nim znajdują się potrzebne tu m.in. definicje preprocesora

// definicje zmiennych globalnych przechowujących cyfry do wyświetlania
// volatile – ponieważ będą wykorzystywane do odczytu i zapisu zarówno w przerwaniu i programie
// głównym. Trzeba więc wyłączyć optymalizację dostępu do nich. (zmienne ulotne)
volatile uint8_t cy1;
volatile uint8_t cy2;
volatile uint8_t cy3;
volatile uint8_t cy4;


// definicja tablicy zawierającej definicje bitowe cyfr LED
const uint8_t cyfry[15] PROGMEM = {

			0xC0,	// 0
			0xF9,	// 1   0b10011111
			0xA4,	// 2
			0xB0,	// 3
			0x99,	// 4   0b10011001
			0x92,	// 5
			0x82,	// 6
			0xD8,	// 7
			0x80,	// 8
			0x90,	// 9   0b00001001
		    0xFF	// NIC (puste miejsce)
};



// ****** definicja funkcji inicjalizującej pracę z wyświetlaczem multipleksowanym
void d_led_init(void)
{
	LED_DATA_DIR = 0xFF;   					// wszystkie piny portu C jako WYJŚCIA(katody)
	LED_DATA = 0xFF;						// wygaszenie wszystkich katod – stan wysoki
	ANODY_DIR |= CA1 | CA2 | CA3 | CA4;		// 4 piny portu A jako WYJŚCIA (anody wyświetlaczy)
	ANODY_PORT |= CA1 | CA2 | CA3  | CA4;	// wygaszenie wszystkich wyświetlaczy - anody

	// ustawienie TIMER0
	TCCR0 |= (1<<WGM01);					// tryb CTC Mode2 Nota PDF
	TCCR0 |= (1<<CS02)|(1<<CS00);			// preskaler = 1024
	OCR0 = 38;								// dodatkowy podział przez 39 (rej. przepełnienia)
	TIMSK |= (1<<OCIE0);					// zezwolenie na przerwanie CompareMatch
}


// ================= PROCEDURA OBSŁUGI PRZERWANIA – COMPARE MATCH
ISR(TIMER0_COMP_vect)
{
	static uint8_t licznik=1;										// zmienna do przełączania kolejno anod wyświetlacza

	ANODY_PORT = (ANODY_PORT | MASKA_ANODY);						// wygaszenie wszystkich wyświetlaczy

	if(licznik==1) 		LED_DATA = pgm_read_byte( &cyfry[cy1] );	// gdy zapalony wyśw.1 podaj stan zmiennej c1
	else if(licznik==2) LED_DATA = pgm_read_byte( &cyfry[cy2] );	// gdy zapalony wyśw.2 podaj stan zmiennej c2
	else if(licznik==4) LED_DATA = pgm_read_byte( &cyfry[cy3] );	// gdy zapalony wyśw.3 podaj stan zmiennej c3
	else if(licznik==8) LED_DATA = pgm_read_byte( &cyfry[cy4] );	// gdy zapalony wyśw.4 podaj stan zmiennej c4

	ANODY_PORT = (ANODY_PORT & ~MASKA_ANODY) | (~licznik & MASKA_ANODY);			// cykliczne przełączanie kolejnej anody w każdym przerwaniu

	// operacje cyklicznego przesuwania bitu zapalającego anody w zmiennej licznik
	licznik <<= 1;					// przesunięcie zawartości bitów licznika o 1 w lewo
	if(licznik>8) licznik = 1;		// jeśli licznik większy niż 8 to ustaw na 1
}

