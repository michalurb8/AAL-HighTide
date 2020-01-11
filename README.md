TODO dokumentacja, pomiary czasu

# Problem - Żeglowanie w czasie przypływu
## Michał Urbański

## Program umożliwia wykonywanie następujących poleceń:
h - Display help 
1 - Load data from data.txt file
2 - Load data from any .txt file
3 - Load data manually
p - Print loaded data
s - Solve and display
b - Brute force solution
g - Generate random data to other.txt
q - Exit

## Pliki z danymi wejściowymi:
plik zawiera w pierwszej linii jedną liczbę całkowitą, rozmiar mapy N
W nastepnych N liniach znajduje się po N liczb całkowitych z zakresu 0-M, elementów mapy
Przykład zawartości pliku:
3
1 0 5
5 4 3
2 6 2

## Metoda rozwiązania:
Dla danego momentu czasu t sprawdzanie metodą "przejścia wzdłuż prawej ściany" czy przejście jest możliwe.
Na pewno nie da się przepłynąć przez mapę w czasie krótszym niż wartość wysokości pierwszego i ostatniego pola, więc sprawdzanie zaczyna się od maksimum z tych wartości.
Następnie sprawdzane są coraz większe (przy każdej iteracji 1.5x większe niż poprzednie) wartości czasu t aż do osiągnięcia takiej, w której przepłynięcie jest możliwe.
Gdy znana jest taka wartość, binarnie przeszukujemy przestrzeń pomiędzy nią a największą dotychczas znalezioną wartością czasu, w której przejście nie jest możliwe.
Złożoność czasowa to O(N*log(M)).
Złożoność pamięciowa to O(1).

## Pliki źródłowe programu:
main.cpp - wywołuje główną metodę klasy Tide
Tide.cpp, Tide.h - służy komunikacji programu z użytkownikiem i wczytywaniu danych
Solution.cpp, Solution.h - implementacja algorytmu

## Założenia:
Zakres wartości N: 1 - 10^4
Zakres wartości M: 1 - 10^9


## Generatory danych testowych:
Jeden generuje mapę NxN wartości zupełnie pseudolosowych
Drugi generuje mapę NxN do testowania przypadków pesymistycznych