/*
 * Tomasz Kowalczyk
 * Lukasz Zawistowicz
 */

#include "utils.h"

/*
 * Zadanie 2. Zaswiecenie diod LED po przycisnieciu przycisku PIN0
 */
void button_led(){

    DDRB  =  0b00000000;            // Ustawienie PB0-7 na wejscie
    PORTB =  0b00000001;            // PB0 zmieniamy wartosc logiczna
    DDRA  =  0b11111111;            // wyjscie dla wszystkich z PA

    while(1)
    {
        if(PINB & 0b00000001)           // jesli pin B jest przycisniety
        {
            PORTA = 0b11111111;         // ustaw PA0-PA7 na 1 / zaswiecenie doiod LED
        }

        else
        {
            PORTA = 0b00000000;         // inaczej zgas wszystkie diody
        }

    }
}


/*
 * Zadanie 3. Mruganie diodami w formie weza
 */
void snake()
{
    DDRA = 0xff;        // PA0-7 wyjscie
    PORTA = 0xff;
    const int size = 8;

    char arr[size];

    arr[0] = 0b00000001;
    arr[1] = 0b00000010;
    arr[2] = 0b00000100;
    arr[3] = 0b00001000;
    arr[4] = 0b00010000;
    arr[5] = 0b00100000;
    arr[6] = 0b01000000;
    arr[7] = 0b10000000;

    int it = 0;
    int val = 1;

    while(1){

        //PORTA |= (1<<it);
        PORTA = arr[it];
        _delay_ms(1000);

            if(it == size-1){
                val = -1;
            }else if(it == 0){
                val = 1;
            }

        it += val;
    }
}

/*
 * Zadanie 4 Przygasanie swiatelek
 */

void przygasanie_led()
{
    DDRA = 0xff;                                // Do rejestru DDRA wpisujemy wartosc 11111111 aby wszystkie piny Porty byly wyjsciami
    PORTA = 0xff;                               // wylaczenie wszystkich diod (Katoda) 0b11111111;

    int t = 1000;
    int x = 0;
    int minus = 1;

    while(1)
    {
        PORTA = 0b11111111;                     // wylaczenie wszystkich diod (Katoda)
        wait(t - x);                          // // 1000, 999, 998, 997 ... 0, 1, 2, 3, ,..., 1000
        PORTA = 0b00000000;
        wait(x);                              // 0, 1, 2, 3, ... 1000, 999, 998 , ..., 0

        if(x == 1000){
            minus = -1;
        }

        else if(x == 0){
            minus = 1;
        }

        x += minus;

    }
}

/*
 * Fala swiatelek
 */

void rozjasnienie(liczba, t, i)
{
    int x=0, minus=1, k=0;
    for (int j=0; j<t; j++)
    {
        PORTA  = 0b11111111; // wylaczenie
        wait(t - x);
        PORTA = ~liczba; // wlaczenie
        wait(x);

        x = x + minus;

    }
    PORTA = ~liczba;
}

void przygasniecie(liczba, t, i)
{
    int x=t, minus=1;
    for (int j=0; j<t; j++)
    {
        PORTA = 0b11111111;
        wait(t - x);
        PORTA = ~liczba;
        wait(x);

        x = x - minus;

    }
    PORTA = ~liczba;
}

void wave()
{
    DDRA = 0xff;                                // Do rejestru DDRA wpisujemy wartosc 11111111 aby wszystkie piny Porty byly wyjsciami
    PORTA = 0x00;                               // wylaczenie wszystkich diod (Katoda) 0b11111111;

    while(1)
    {
        uint8_t i, liczba=1;

        for (i=0; i<8; i++){


            rozjasnienie(liczba, 1000, i);
            rozjasnienie(liczba * 2, 1000);
            przygasniecie(liczba, 1000);
            przygasniecie(liczba * 2, 1000, i);
            liczba = liczba * 2;
            //t = t - 100;
            //wait(500);
        }
    }
}
