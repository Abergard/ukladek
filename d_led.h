
#ifndef _d_led_h		// dyrektywy zabezpieczające przed wielokrotnym dołączaniem
#define _d_led_h		// tego samego pliku nagłówkowego jeśli będzie dołączany
						// w wielu różnych plikach programu

// definicje portów i pinów wyświetlacza używanych dla ułatwienia w programie jako stałe preprocesora
#define 	LED_DATA 	PORTC	// port z podłączonymi segmentami
#define		LED_DATA_DIR DDRC	// rejestr kierunku portu katod wyświetlaczy
#define 	ANODY_PORT 	PORTA	// port z podłączonymi anodami- 4 bity najmłodsze
#define 	ANODY_DIR 	DDRA	// rejestr kierunku portu anod wyświetlaczy


#define 	CA1 	(1<<PC0)		// CA1 oznacza bit nr.0 portu C
#define 	CA2 	(1<<PC1)		// CA2 oznacza bit nr.1 portu C
#define 	CA3 	(1<<PC2)		// CA3 oznacza bit nr.2 portu C
#define 	CA4 	(1<<PC3)		// CA4 oznacza bit nr.3 portu C

#define MASKA_ANODY (CA1|CA2|CA3|CA4) 



#define NIC 10

// same DEKLARACJE zmiennych globalnych na potrzeby wykorzystania ich w innych plikach projektu
// przydomek externpowoduje, iż te zmienne będą dostępne we wszystkich modułach, które dołączą plik
// d_led.h za pomocą dyrektywy #include
extern volatile uint8_t cy1;
extern volatile uint8_t cy2;
extern volatile uint8_t cy3;
extern volatile uint8_t cy4;



void d_led_init(void);

#endif	// koniec _d_led_h

