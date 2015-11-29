# ukladek

DDRx (x = A,B,C,D) opisuje stan portow, tzn. czy s± to porty wejscia, czy wyjscia.
Wszystkie porty domyslnie sa portami wejscia.
Aby ustawic port na port wyjsciowy, nalezy w odpowiednim rejestrze, na odpowiednim miejscu usawic 1
np. DDRA = 0b00000001 - ustawia jeden z portow A jako wyjsciowy, a reszte jako wejsciowe.

Porty wejscia oznaczaja, ze sygnal idzie z urzadzenia podlaczego do tego portu np z klawiatury do portu.
Porty wyjscia oznaczaja, ze sygnal idzie z portu do urzedzania np. z portu do diody.

Po podlaczeniu do portu urz±dzenia i ustawieniu portu na port wejscia nalezy wlaczyc rezystor podciagajacy.
Aby to zrobic nalezy ustawic stan wysoki na tym samym porcie np. DDRA = 0b00000000 (ustawienie portu na port wejscia),
PORTA = 0b00000001 (wlaczenie rezystora podciagajacego).