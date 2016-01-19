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
#include "d_led.h"				// do³¹czenie naszego pliku nag³ówkowego (obs³uga LED)
#include <avr/interrupt.h>



#define LED_PIN (1<<PD0)    											// definicja pinu do którego pod³aczamy diode LED
#define LED_ON PORTD &= ~LED_PIN										// makrodefinicja - zalaczenia diody
#define LED_OFF PORTD |= LED_PIN										// makrodefinicja - wylaczenie diody
#define LED_TOG PORTD ^= LED_PIN										// makrodefinicja - zmiana stanu diody
#define K1_LEFT (1<<PD7)
#define K2_RIGHT (1<<PD6)
#define K3_ENTER (1<<PD5)
#define K4_DOWN (1<<PD4)


uint8_t znak_buzka[] = {14,17,27,17,17,21,17,14};									    // wzór znaku buzki w pamiêci RAM
uint8_t pressed_button(uint8_t key);

uint8_t pressed_button(uint8_t key){
	if (!(PIND & key)){
		_delay_ms(80);																	// czas drgañ styków
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

void led_end(){
			DDRD |= LED_PIN;
			int i = 0;
			while(i < 10){
				LED_TOG;
				_delay_ms(2000);
				i++;
			}
			LED_OFF;
	}


void Timer_60(){

	// ****** inicjalizacja *********
	d_led_init();   		// inicjalizacja wyœwietlacza multipleksowanego

	sei();			        // w³¹czenie globalnego zezwolenia na przerwania

	uint16_t licznik=0;
	uint8_t d1,d2,d3,d4;

		//**********************  pêtla g³ówna
		while(1)
		{
			licznik++;

			d1=licznik/1000;
			if(d1) cy1=d1; else cy1=NIC;
			d2=(licznik-(d1*1000))/100;
			if(d2) cy2=d2; else cy2=(licznik>999)?0:NIC;
			d3=(licznik-(d1*1000)-(d2*100))/10;
			if(d3) cy3=d3; else cy3=(licznik>99)?0:NIC;
			d4=(licznik-(d1*1000)-(d2*100)-(d3*10));
			cy4=d4;
			_delay_ms(100);
	       if(d1 == 1) {
	    	   led_end();

	       }
		}
}

void move_right(){
	LED_ON;
}

void move_left(){
	led_win();
}

void move_down(){
	led_win();
}

void enter(){
	led_win();
}

int main(void)
{
	lcd_cursor_on();
	lcd_blink_on();

	DDRA |= (1<<PA7);																// ustawiamy kierunek linii podœwietlenia LCD jako WYJŒCIE
	PORTA |= (1<<PA7);																// za³¹czamy podœwietlenie LCD - stan wysoki

	lcd_init();
	lcd_cls();
	//lcd_cursor_on();

	// za³adowanie znaków do pamiêci CGRAM
    //lcd_defchar(0x80, znak_buzka);
	//lcd_locate(1,10);
	//lcd_str("\x80");

	lcd_locate(0,6);
	lcd_str("witaj");

	lcd_locate(1,0);
	lcd_str(" Menu");


// Piny klawiszy - wejscia
	DDRD &= ~(K1_LEFT | K2_RIGHT | K3_ENTER | K4_DOWN);
// Podciagniecie Pinów pod VCC
	PORTD |= K1_LEFT | K2_RIGHT | K3_ENTER | K4_DOWN;

	while(1){
		if (pressed_button(K1_LEFT)) move_left();
		if (pressed_button(K2_RIGHT)) move_right();
		if (pressed_button(K3_ENTER)) enter();
		if (pressed_button(K4_DOWN)) move_down();
	}

//Timer_60();

}





