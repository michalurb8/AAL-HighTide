# Problem - Żeglowanie w czasie przypływu
## Michał Urbański

## Program umożliwia wykonywanie następujących poleceń:
1 - Load data from default.txt file <br />
2 - Load data from any .txt file <br />
3 - Load data manually <br />
p - Print loaded data <br />
g - Generate random data to default.txt <br />
s - Solve and display the result <br />
l - Solve in a loop, show the time <br />
d - Perform the default test, results in results.txt <br />
c - Perform a custom test, results in results.txt <br />
h - Display this help message <br />
q - Exit <br />

## Pliki z danymi wejściowymi:
Plik zawiera w pierwszej linii jedną liczbę całkowitą, rozmiar mapy N <br />
W nastepnych N liniach znajduje się po N liczb całkowitych z zakresu 0-M, elementów mapy <br />
Przykład zawartości pliku: <br /> <br />
3 <br />
1 0 5 <br />
5 4 3 <br />
2 6 2 <br /> <br />

## Metoda rozwiązania:
Dla danego momentu czasu t sprawdzanie metodą "przejścia wzdłuż prawej ściany" czy przejście jest możliwe. <br />
Na pewno nie da się przepłynąć przez mapę w czasie krótszym niż wartość wysokości pierwszego i ostatniego pola, więc sprawdzanie zaczyna się od maksimum z tych wartości. <br />
Następnie sprawdzane są coraz większe (przy każdej iteracji 1.5x większe niż poprzednie) wartości czasu t aż do osiągnięcia takiej, w której przepłynięcie jest możliwe. <br />
Gdy znana jest taka wartość, binarnie przeszukujemy przestrzeń pomiędzy nią a największą dotychczas znalezioną wartością czasu, w której przejście nie jest możliwe. <br />
Złożoność czasowa to O(N*log(M)). <br />
Złożoność pamięciowa to O(1). <br />

## Pliki źródłowe programu:
main.cpp - wywołuje główną metodę klasy Tide <br />
Tide.cpp, Tide.h - służy komunikacji programu z użytkownikiem i wczytywaniu danych <br />
Solution.cpp, Solution.h - implementacja algorytmu <br />
Timer.cpp, Timer.h - prosta klasa służąca do pomiaru czasu <br />

## Założenia:
Zakres wartości N: 1 - 10^9 (testowanie jest realne dla N <= 10^4) <br />
Zakres wartości M: 1 - 10^9 <br />


## Generatory danych testowych:
Jeden generuje mapę NxN wartości zupełnie pseudolosowych <br />