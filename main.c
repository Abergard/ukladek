/*
 * Tomasz Kowalczyk
 * Lukasz Zawistowicz
 */

 //#define F_CPU 16000000UL

#include <avr/io.h> // zawiera on definicje, odpowiednie dla naszego mikrokontrolera.
#include <util/delay.h>
#include <stdint.h>
#include <avr/interrupt.h>

//#define sbi(x,y) x |= _BV(y) //set bit - using bitwise OR operator
//#define cbi(x,y) x &= ~(_BV(y)) //clear bit - using bitwise AND operator
//#define tbi(x,y) x ^= _BV(y) //toggle bit - using bitwise XOR operator
//#define is_high(x,y) (x & _BV(y) == _BV(y)) //check if the y'th bit of register 'x' is high ... test if its AND with 1 is 1
//#define is_low(x,y) ((x & _BV(y)) == 0) //check if the input pin is low

#define sbi(x,y) x |= _BV(y) //set bit
#define cbi(x,y) x &= ~(_BV(y)) //clear bit
#define tbi(x,y) x ^= _BV(y) //toggle bit
#define is_high(x,y) ((x & _BV(y)) == _BV(y))

#define wait(czas) for(int i=0;i<(czas);i++) _delay_us(1);

// Funkcja testowa do wykonywania testow
void test()
{
    DDRA = 0xff;                                // Do rejestru DDRA wpisujemy wartoscc 11111111 aby wszystkie piny Porty byly wysciowymi
    PORTA = 0xff;                               // wylaczenie wszystkich diod (Katoda) 0b11111111;

    while(1)
    {
        uint8_t i, liczba=3;
        for (i=0; i<8; i++){
            PORTA = ~liczba;                    // operator negacji. Do portu przekazujemy odpowiednio 111111110, 11111101
            liczba = liczba * 2;                // 1,2,4,8,16,32.64,128   //liczba = 1 zapalanie diody w kolejnoœci / liczba = 2 zapalanie dwóch diod

            _delay_ms(5000);

        }

        PORTA = 0xff;
        _delay_ms(5000);

    }
}



/* Zadanie 1: chcemy zmusiæ nasz¹ diodê do mrugania, co jedn¹ sekundê, czyli z czêstotliwoœci¹ 1Hz
 * chcemy zmusic nó¿kê mikrokontrolera by przyjmowa³a stan niski lub wysoki
 * Rejestry s¹ to komórki w specjalnej pamiêci do której procesor ma bezpoœredni, szybki dostêp
 * Wszystkie nó¿ki na samym pocz¹tku, po w³¹czeniu zasilania s¹ domyœlnie wejœciami, odpowiada za to rejestr "DDRx" (gdzie x to literka portu)
 * Aby nasze diody sta³y siê wyjœciami, musimy zapisaæ do rejestru "DDRB" wartoœæ 2 (czyli binarnie 00000010). Stan logiczny portu kontroluje rejestr "PORTx"
 * (gdzie x to literka portu)
 *
 *
 *
 * Ka¿dy port posiada 3 w³asne rejestry:
    Rejestr danych (PORTx) odpowiada za stany logiczne na porcie (wysoki lub niski), kiedy pin jest ustawiony jako wyjœcie, w przeciwnym wypadku - kiedy port jest wejœciem, rejestr ten w³¹cza lub wy³¹cza rezystor podci¹gaj¹cy dla pinu.
    Rejestr kierunku (DDRx) odpowiada za ustawienie pinu jako wejœcia lub jako wyjœcia. Domyœlnie po resecie wszystkie piny s¹ wejœciami, aby ustawiæ wybrany jako wyjœcie, nale¿y ustawiæ odpowiedni bit rejestru DDRx.
    Dane pinów wejœciowych (PINx) jest to rejestr, który mo¿na odczytaæ, aby sprawdziæ stan logiczny na pinie, kiedy ten jest wejœciem. W kodzie mo¿na to zrobiæ przy pomocy instrukcji warunkowej if()
 * */



void mruganie_dioda()
{
    /* Konfiguracja odpowiednich pinów jako wyjœcia
     * POTRB |= (1<<PB1);                           ustawiamy wybrany bit na "1" np. PB0 -> zgaszamy bez zmiany wartoœci pozosta³ych
     * PORTB &= ~(1<<PB2);                          ustawiamy wybrany bit na "0" np. PB0 -> zapalony bez zmiany wartoœci pozosta³ych
     * PORTD |= (1<<5)|(1<<)|(1<<7);                ustawia bity 5, 6 i 7, portu PORTD
     * PORTD &= ~(1<<2)|(1<<3);                     zeruje bity 2 i 3, portu PORTD
     * PORTD ^= (1<<1)|(1<<2);                      odwraca bity 1 i 2, portu PORTD
     * PORTD & PD2;                                 zwraca wartoœæ 1, je¿eli pin 2 portu PORTD jest ustawiony (ma wartoœæ 1)
     */

    DDRA = 0xff;                                // Do rejestru DDRA wpisujemy wartoœc 11111111 aby wszystkie piny Porty by³y wyjœciami
    PORTA = 0xff;                               // wy³aczenie wszystkich diod (Katoda) 0b11111111;

    while(1){


        PORTA &= ~(1<<PA0);                     // zapalenie diody 0b11111110
        _delay_ms(1000);
        PORTA |= (1<<PA0);                      // zgaszenie diody 0b11111111
        _delay_ms(1000);


    }
}

/*
 * Zadanie 2. Zaœwiecenie diod LED po przyciœniêciu przycisku PIN0
 */
void button_led(){

    DDRB  =  0b00000000;            // Ustawienie PB0-7 na wejœcie
    PORTB =  0b00000001;            // PB0 zmieniamy wartoœc logiczna
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
 * Zadanie 3. Mruganie diodami w formie wê¿a
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
 * Zadanie 4 Przygasanie œwiate³ek
 */

void przygasanie_led()
{
    DDRA = 0xff;                                // Do rejestru DDRA wpisujemy wartoœc 11111111 aby wszystkie piny Porty by³y wyjœciami
    PORTA = 0xff;                               // wy³aczenie wszystkich diod (Katoda) 0b11111111;

    int t = 1000;
    int x = 0;
    int minus = 1;

    while(1)
    {
        PORTA = 0b11111111;                     // wy³aczenie wszystkich diod (Katoda)
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
 * Fala œwiate³ek
 */

void rozjasnienie(liczba, t, i)
{
    int x=0, minus=1, k=0;
    for (int j=0; j<t; j++)
    {
        PORTA  = 0b11111111; // wy³aczenie
        wait(t - x);
        PORTA = ~liczba; // w³aczenie
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
    DDRA = 0xff;                                // Do rejestru DDRA wpisujemy wartoœc 11111111 aby wszystkie piny Porty by³y wyjœciami
    PORTA = 0x00;                               // wy³aczenie wszystkich diod (Katoda) 0b11111111;

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

int main()
{
}
