
#ifndef _d_led_h		// dyrektywy zabezpieczaj�ce przed wielokrotnym do��czaniem
#define _d_led_h		// tego samego pliku nag��wkowego je�li b�dzie do��czany
						// w wielu r�nych plikach programu

// definicje port�w i pin�w wy�wietlacza u�ywanych dla u�atwienia w programie jako sta�e preprocesora
#define 	LED_DATA 	PORTC	// port z pod��czonymi segmentami
#define		LED_DATA_DIR DDRC	// rejestr kierunku portu katod wy�wietlaczy
#define 	ANODY_PORT 	PORTB	// port z pod��czonymi anodami- 4 bity najm�odsze
#define 	ANODY_DIR 	DDRB	// rejestr kierunku portu anod wy�wietlaczy


#define 	CA1 	(1<<PC0)		// CA1 oznacza bit nr.0 portu C
#define 	CA2 	(1<<PC1)		// CA2 oznacza bit nr.1 portu C
#define 	CA3 	(1<<PC2)		// CA3 oznacza bit nr.2 portu C
#define 	CA4 	(1<<PC3)		// CA4 oznacza bit nr.3 portu C

#define MASKA_ANODY (CA1|CA2|CA3|CA4)


#define NIC 10

// same DEKLARACJE zmiennych globalnych na potrzeby wykorzystania ich w innych plikach projektu
// przydomek extern powoduje, i� te zmienne b�d� dost�pne we wszystkich modu�ach, kt�re do��cz� plik
// d_led.h za pomoc� dyrektywy #include
extern volatile uint8_t cy1;
extern volatile uint8_t cy2;
extern volatile uint8_t cy3;
extern volatile uint8_t cy4;



void d_led_init(void);

#endif	// koniec _d_led_h

