# ukladek

DDRx (x = A,B,C,D) opisuje stan portow, tzn. czy są to porty wejscia, czy wyjscia.
Wszystkie porty domyslnie sa portami wejscia.
Aby ustawic port na port wyjsciowy, nalezy w odpowiednim rejestrze, na odpowiednim miejscu usawic 1
np. DDRA = 0b00000001 - ustawia jeden z portow A jako wyjsciowy, a reszte jako wejsciowe.

Porty wejscia oznaczaja, ze sygnal idzie z urzadzenia podlaczego do tego portu np z klawiatury do portu.
Porty wyjscia oznaczaja, ze sygnal idzie z portu do urzedzania np. z portu do diody.

Po podlaczeniu do portu urządzenia i ustawieniu portu na port wejscia nalezy wlaczyc rezystor podciagajacy.
Aby to zrobic nalezy ustawic stan wysoki na tym samym porcie np. DDRA = 0b00000000 (ustawienie portu na port wejscia),
PORTA = 0b00000001 (wlaczenie rezystora podciagajacego).

##Zadanie 1
Kazdy port posiada 3 wlasne rejestry:
Rejestr danych (PORTx) odpowiada za stany logiczne na porcie (wysoki lub niski), kiedy pin jest ustawiony jako wyjscie, w przeciwnym wypadku - kiedy port jest wejsciem, rejestr ten wlacza lub wylacza rezystor podciagajacy dla pinu.
Rejestr kierunku (DDRx) odpowiada za ustawienie pinu jako wejscia lub jako wyjscia. Domyslnie po resecie wszystkie piny sa wejsciami, aby ustawic wybrany jako wyjscie, nalezy ustawic odpowiedni bit rejestru DDRx.
Dane pinow wejsciowych (PINx) jest to rejestr, ktory mozna odczytac, aby sprawdzic stan logiczny na pinie, kiedy ten jest wejsciem. W kodzie mozna to zrobic przy pomocy instrukcji warunkowej if())

- Chcemy zmusic nasza diode do mrugania, co jedna sekunde, czyli z czestotliwoscia 1Hz
(Chcemy zmusic nozke mikrokontrolera by przyjmowala stan niski lub wysoki
Rejestry sa to komorki w specjalnej pamieci do ktorej procesor ma bezposredni, szybki dostep
Wszystkie nozki na samym poczatku, po wlaczeniu zasilania sa domyslnie wejsciami, odpowiada za to rejestr "DDRx" (gdzie x to literka portu)
Aby nasze diody staly sie wyjsciami, musimy zapisac do rejestru "DDRB" wartosc 2 (czyli binarnie 00000010). Stan logiczny portu kontroluje rejestr "PORTx"
(gdzie x to literka portu)

- Zaswiecenie diod LED po przycisnieciu przycisku PIN0

- Mruganie diodami w formie weza

- Przygasanie swiatelek

##Zadanie 2

##Zadanie 3
- Prymitywny stoper (Chcemy by zegar, wykorzystujac przerwania, inkrementowal nam licznik).

##Zadanie 4
- Wyswietlanie na wywietlaczu LED numeru przycisnietego przycisku klawiatury.
