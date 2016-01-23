//-----------------------------------------------------------------------------------------------------------
// *** Obs�uga wy�wietlaczy alfanumerycznych zgodnych z HD44780 ***
//
// - Sterowanie: tryb 4-bitowy
// - Dowolne przypisanie ka�dego sygna�u steruj�cego do dowolnego pinu mikrokontrolera
// - Praca z pinem RW pod��czonym do GND lub do mikrokontrolera (sprawdzanie BusyFLAG - szybkie operacje LCD)
//

#ifndef LCD_H_
#define LCD_H_
//----------------------------------------------------------------------------------------
//
//		Parametry pracy sterownika
//
//----------------------------------------------------------------------------------------
// rozdzielczo�� wy�wietlacza LCD (wiersze/kolumny)
#define LCD_ROWS 2		// ilo�� wierszy wy�wietlacza LCD
#define LCD_COLS 16	    // ilo�� kolumn wy�wietlacza LCD

// tu ustalamy za pomoc� zera lub jedynki czy sterujemy pinem RW
//	0 - pin RW pod��czony na sta�e do GND
//	1 - pin RW pod��czony do mikrokontrolera
#define USE_RW 1

//----------------------------------------------------------------------------------------
//
//		Ustawienia sprz�towe po��cze� sterownika z mikrokontrolerem
//
//----------------------------------------------------------------------------------------
// tu konfigurujemy port i piny do jakich pod��czymy linie D7..D4 LCD
#define LCD_D7PORT  A
#define LCD_D7 3				// D7-PA3
#define LCD_D6PORT  A
#define LCD_D6 2				// D6-PA2
#define LCD_D5PORT  A
#define LCD_D5 1				// D5-PA1
#define LCD_D4PORT  A
#define LCD_D4 0				// D4-PA0



// tu definiujemy piny procesora do kt�rych pod��czamy sygna�y RS,RW, E
#define LCD_RSPORT A
#define LCD_RS 5

#define LCD_RWPORT A
#define LCD_RW 6

#define LCD_EPORT A
#define LCD_E 4
//------------------------------------------------  koniec ustawie� sprz�towych ---------------


//----------------------------------------------------------------------------------------
//****************************************************************************************
//*																						 *
//*		U S T A W I E N I A   KOMPILACJI												 *
//*																						 *
//*		W��czamy kompilacj� komend u�ywanych lub wy��czamy nieu�ywanych					 *
//*		(dzi�ki temu regulujemy zaj�to�� pami�ci FLASH po kompilacji)					 *
//*																						 *
//*		1 - oznacza W��CZENIE do kompilacji												 *
//*		0 - oznacza wy��czenie z kompilacji (funkcja niedost�pna)						 *
//*																						 *
//****************************************************************************************
//----------------------------------------------------------------------------------------

#define USE_LCD_LOCATE	1			// ustawia kursor na wybranej pozycji Y,X (Y=0-3, X=0-n)
#define USE_LCD_CHAR 	1			// wysy�a pojedynczy znak jako argument funkcji
#define USE_LCD_DEFCHAR		1		// wysy�a zdefiniowany znak z pami�ci RAM
#define USE_LCD_CURSOR_ON 		1	// obs�uga w��czania/wy��czania kursora
#define USE_LCD_CURSOR_BLINK 	1	// obs�uga w��czania/wy��czania migania kursora
#define USE_LCD_CURSOR_HOME 	1	// ustawia kursor na pozycji pocz�tkowej

//------------------------------------------------  koniec ustawie� kompilacji ---------------



// definicje adres�w w DDRAM dla wy�wietlacza  2wierszowego
#define LCD_LINE1 0x00		// adres 1 znaku 1 wiersza
#define LCD_LINE2 0x40		// adres 1 znaku 2 wiersza



// Makra upraszczaj�ce dost�p do port�w
// *** PORT
#define PORT(x) SPORT(x)
#define SPORT(x) (PORT##x)
// *** PIN
#define PIN(x) SPIN(x)
#define SPIN(x) (PIN##x)
// *** DDR
#define DDR(x) SDDR(x)
#define SDDR(x) (DDR##x)


// Komendy steruj�ce
#define LCDC_CLS					0x01
#define LCDC_HOME					0x02
#define LCDC_ENTRY					0x04
	#define LCDC_ENTRYR					0x02
	#define LCDC_ENTRYL					0
	#define LCDC_MOVE					0x01
#define LCDC_ONOFF					0x08
	#define LCDC_DISPLAYON				0x04
	#define LCDC_CURSORON				0x02
	#define LCDC_CURSOROFF				0
	#define LCDC_BLINKON				0x01
#define LCDC_SHIFT					0x10
	#define LCDC_SHIFTDISP				0x08
	#define LCDC_SHIFTR					0x04
	#define LCDC_SHIFTL					0
#define LCDC_FUNC					0x20
	#define LCDC_FUNC8B					0x10
	#define LCDC_FUNC4B					0
	#define LCDC_FUNC2L					0x08
	#define LCDC_FUNC1L					0
	#define LCDC_FUNC5x10				0x04
	#define LCDC_FUNC5x7				0
#define LCDC_SET_CGRAM				0x40
#define LCDC_SET_DDRAM				0x80





// deklaracje funkcji na potrzeby innych modu��w
void lcd_init(void);								// W��CZONA na sta�e do kompilacji
void lcd_cls(void);									// W��CZONA na sta�e do kompilacji
void lcd_str(const char * str);							// W��CZONA na sta�e do kompilacji

void lcd_locate(uint8_t y, uint8_t x);				// domy�lnie W��CZONA z kompilacji w pliku lcd.c

void lcd_char(char c);								// domy�lnie wy��czona z kompilacji w pliku lcd.c
void lcd_str_P(const char * str);							// domy�lnie wy��czona z kompilacji w pliku lcd.c
void lcd_str_E(char * str);							// domy�lnie wy��czona z kompilacji w pliku lcd.c
void lcd_int(int val);								// domy�lnie wy��czona z kompilacji w pliku lcd.c
void lcd_hex(uint32_t val);								// domy�lnie wy��czona z kompilacji w pliku lcd.c
void lcd_defchar(uint8_t nr, uint8_t *def_znak);	// domy�lnie wy��czona z kompilacji w pliku lcd.c
void lcd_defchar_P(uint8_t nr, const uint8_t *def_znak);	// domy�lnie wy��czona z kompilacji w pliku lcd.c
void lcd_defchar_E(uint8_t nr, uint8_t *def_znak);	// domy�lnie wy��czona z kompilacji w pliku lcd.c

void lcd_home(void);								// domy�lnie wy��czona z kompilacji w pliku lcd.c
void lcd_cursor_on(void);							// domy�lnie wy��czona z kompilacji w pliku lcd.c
void lcd_cursor_off(void);							// domy�lnie wy��czona z kompilacji w pliku lcd.c
void lcd_blink_on(void);							// domy�lnie wy��czona z kompilacji w pliku lcd.c
void lcd_blink_off(void);							// domy�lnie wy��czona z kompilacji w pliku lcd.c

void lcd_write_cmd(uint8_t cmd);

#endif /* LCD_H_ */
