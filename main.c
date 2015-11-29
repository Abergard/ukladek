/*
 * Tomasz Kowalczyk
 * Lukasz Zawistowicz
 */

//#define F_CPU 16000000UL

#include <avr/io.h> // zawiera on definicje, odpowiednie dla naszego mikrokontrolera.
#include <util/delay.h>
#include <stdint.h>
#include <avr/interrupt.h>

#define sbi(x,y) x |= _BV(y) //set bit
#define cbi(x,y) x &= ~(_BV(y)) //clear bit
#define tbi(x,y) x ^= _BV(y) //toggle bit
#define is_high(x,y) ((x & _BV(y)) == _BV(y))

#define wait(czas) for(int i=0;i<(czas);i++) _delay_us(1);

/* Zadania zestaw 2 */

// Zadanie 2.1

/* Przerwanie (ang. interrupt) sygnal powodujacy zmiane przeplywu sterowania, niezaleznie od aktualnie
   wykonywanego programu. Pojawienie sie przerwania powoduje wstrzymanie aktualnie wykonywanego programu i wykonanie przez procesor kodu procedury.
   Na koncu wydaje instrukcje powrotu z przerwania, kt�ra powoduje powr�t do programu realizowanego przed przerwaniem.
*/

// dodawanie binarne za pomoca LED
ISR(INT0_vect)
{
    static uint8_t a = 0;
    ++a;
    uint8_t b = 1;
    b &= PORTA;
    PORTA = ~(a*2);
    PORTA |= b;

}

void setup_interrupt()
{
    DDRA = 0xff;                            // DDRA - wyjscie
    DDRD  =  0b00000000;                    // DDRD - wejscie
    PORTD =  0b00000100;                    // PD2
    MCUCR |= (1 << ISC01) | (0 << ISC00);   // MCUR- MCU Control Register
    GICR |= (1 << INT0);                    // Int0 = PD2 posiada konfigurowalny spos�b wyzwalania
                                            // GICR General interrupt control register
    sei();
}

/*
 * Miganie pierwsza dioda
 */
void blink()
{
    DDRA = 0xff;                                // Do rejestru DDRA wpisujemy wartosc 11111111 aby wszystkie piny Porty byly wyjsciami
    PORTA = 0xff;                               // wylaczenie wszystkich diod (Katoda) 0b11111111;

    while(1)
    {
        PORTA &= ~(1<<PA0);                     // zapalenie diody 0b11111110
        _delay_ms(1000);
        PORTA |= (1<<PA0);                      // zgaszenie diody 0b11111111
        _delay_ms(1000);
    }
}

// Koniec zadania 2.1

// Zadanie 2.2
// Rozjasnianie i przyciemnianie diody dwa przyciski

/* funkcje pomocnicze */
void increase()
{
    OCR0++;
}

void decrease()
{
    OCR0--;
}

void setup(){
    DDRD = 0x00;
    DDRB = 0xff;
    PORTD = 3;
    TCCR0 = (1 << WGM01) | (1 << WGM00) | (1 << COM01) | (1 << CS01);
    TCNT0 = 0;
    OCR0 = 0;
}

int zad22(void)
{
    setup();
    while(1)
    {
        if(!(PIND & 1)){
            increase();
        }

        if(!(PIND & 2)){
            decrease();
        }
        wait(500);
    }
}

int main(void)
{
/* Uruchomienie zadania 2.1
 *
 *  setup_interrupt();
 *  blink();
 */

/* Uruchomienie zadania 2.2
 *
 *  zad22();
 *
 */
    zad22();
}
