/*
 *
 *
 * Definicje:
 * RS, RW, E -> linie sterujace
 * D0-D7     -> linie danych wyœwietlacza
 * Praca w trybie 4 bitowym D7-D4
 * Wyœwietlacz ma 2 rodzaje pamieci:
 * CGRAM- pamiec w³asnych znaków(8)
 * DDRAM- Kody ASCII
 */


#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>
#include "LCD/lcd44780.h"
#include <util/delay.h>



// poni¿sz¹ linijkê czasami trzeba wpisaæ w eclipse przed definicjami
// zmiennych w pamiêci EEPROM, ¿eby nie podkreœla³ sk³adni jako b³êdnej
#define EEMEM __attribute__((section(".eeprom")))

const char PROGMEM tab1[] = {"FLASH"};
char EEMEM tab2[] = {"EEPROM"};

uint8_t znak_L[] = {16,16,18,20,24,16,31,0};									    // wzór znaku litery £ w pamiêci RAM
//uint8_t znak_o[] EEMEM = {4,32,14,17,17,17,14,0};								    // wzór znaku litery ó w pamiêci EEPROM
//const uint8_t znak_buzka[] PROGMEM = {14,17,27,17,17,21,17,14};					// wzór znaku buŸki w pamiêci FLASH
//const uint8_t znak_termo[] PROGMEM = {4,10,10,10,17,31,31,14};					// wzór znaku termometru w pamiêci FLASH

volatile uint8_t pwm1, pwm2, pwm3;

int main(void)
{
	DDRA |= (1<<PA7);																// ustawiamy kierunek linii podœwietlenia LCD jako WYJŒCIE
	PORTA |= (1<<PA7);																// za³¹czamy podœwietlenie LCD - stan wysoki

	lcd_init();

//	lcd_str_P(tab1);					// napis z pamiêci FLASH
//	lcd_str_P( PSTR("Linia1") );		// napis z pamiêci FLASH
//	lcd_locate(0,0);
//	lcd_cls();
//	lcd_str("Lukasz");
//	lcd_str_E(tab2);					// napis z pamiêci EEPROM
//	lcd_locate(1,0);

	// za³adowanie znaków do pamiêci CGRAM
//	lcd_defchar(0x80, znak_L);
//	lcd_defchar_E(0x81, znak_o);
//	lcd_defchar_P(0x82, znak_buzka);
//	lcd_defchar_P(0x83, znak_termo);
	lcd_locate(0,0);
	lcd_str("Wesolych");					// napis z pamiêci RAM
	lcd_locate(1,0);
	lcd_str("Swiat ^ ^");				// napis z pamiêci RAM

	// wyœwietlenie w³asnych znaków na LCD
//	lcd_locate(0,0);
//	lcd_str("\x81");
//	lcd_locate(1,10);
//	lcd_str("\x82");
//	lcd_locate(1,7);
//	lcd_str("\x83");
	int pos = 0;
	int value = 1;
	while(1)
	{
		if(value > 0)
			lcd_write_cmd(LCDC_SHIFT | LCDC_SHIFTDISP | LCDC_SHIFTR);
		else
			lcd_write_cmd(LCDC_SHIFT | LCDC_SHIFTDISP | LCDC_SHIFTL);

		_delay_ms(1000);
		if(pos == 15)
		{
			value = -1;
			lcd_cls();
			lcd_locate(0,16);
			lcd_str("Swiat ^ ^");				// napis z pamiêci RAM
			lcd_locate(1,16);
			lcd_str("Wesolych");					// napis z pamiêci RAM
		}

		if(pos == -10)
		{
			value = 1;
			lcd_cls();
			lcd_locate(0,-9);
			lcd_str("Wesolych");					// napis z pamiêci RAM
			lcd_locate(1,-9);
			lcd_str("Swiat ^ ^");				// napis z pamiêci RAM
		}

		pos += value;
	}
}

