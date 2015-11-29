/*
 * Tomasz Kowalczyk
 * Lukasz Zawistowicz
 */

#include "test.h"
#include "utils.h"

// Funkcja testowa do wykonywania testow
void test()
{
    DDRA = 0xff;                                // Do rejestru DDRA wpisujemy wartoscc 11111111 aby wszystkie piny Porty byly wysciowymi
    PORTA = 0xff;                               // wylaczenie wszystkich diod (Katoda) 0b11111111;

    while(1)
    {
        uint8_t i, liczba=3;
        for (i=0; i<8; i++)
        {
            PORTA = ~liczba;                    // operator negacji. Do portu przekazujemy odpowiednio 111111110, 11111101
            liczba = liczba * 2;                // 1,2,4,8,16,32.64,128   //liczba = 1 zapalanie diody w kolejnosci / liczba = 2 zapalanie dwoch diod

            _delay_ms(5000);

        }

        PORTA = 0xff;
        _delay_ms(5000);

    }
}
