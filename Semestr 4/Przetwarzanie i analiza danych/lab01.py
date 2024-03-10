# LAB 01
# gr.220A
# pp53828
# Piotr Pietrusewicz

import numpy as np

# TABLICE

a=np.array([1,2,3,4,5,6,7])
b=np.array([[1,2,3,4,5], [6,7,8,9,10]])

# Wykonaj transpozycję tablicybza pomocą funkcji transpose.

b=np.transpose(b)

# Utwórz i wyświetl tablicę składającą się ze 100 elementów za pomocą
# funkcji arange.

arr = np.arange(100)

# Utwórz i wyświetl tablicę składającą się z 10 liczb w zakresie od 0 do 2.
# Użyj funkcji linspace.

arr = np.linspace(0,2,10)

# Za pomocą funkcji arange utwórz tablicę wartości od 0 do 100 ze
# skokiem wartości co 5.

arr = np.arange(0,101,5)

# LICZBY LOSOWE

# Za pomocą funkcji random utwórz tablicę z 20 liczb losowych rozkładu
# normalnego, zaokrąglonych do dwu miejsc po przecinku.

arr = np.round(np.random.normal(0,1,20),2)

# Wygeneruj losowo 100 liczb całkowitych w zakresie od 1 do 1000.
'''
for i in range(100):
    print(np.random.randint(1,1000))
'''

# Za pomocą funkcji zeros i ones wygeneruj dwie macierze o rozmiarze
# 3×2.

arr1 = np.zeros((3,2))
arr2 = np.ones((3,2))

# Utwórz macierz losową złożoną z liczb całkowitych z zakresu od 0 do
# 100 o rozmiarze 5×5 i nadaj jej typ 32bit.

arr = np.random.randint(0, 101, size=(5,5))
arr_32bit = arr.astype(np.int32)

# ZADANIA

# Wygeneruj tablicę złożoną z losowo wybranych liczb dziesiętnych z 
# zakresu od 0 do 10 (tablica a).

size = 10
a = np.random.random(size) * 10

# Zamień wartości na integer i wstaw w nową tablicę (tablicę b).

b = a.astype(np.int32)

# Znajdź funkcję numpy, która zaokrągli tablicę a do liczb całkowitych.
# Zamień je następnie na typ integer.

a = np.round(a).astype(np.int32)

# Porównaj wyniki z a i b i wyświetl wniosek za pomocą polecenia print.

# print(a)
# print(b)
# print(a==b)

# SELEKCJA DANYCH

b=np.array([[1,2,3,4,5], [6,7,8,9,10]],dtype=np.int32)

# Za pomocą funkcji ndim sprawdź ile wymiarów ma tablica b.

# print(b.ndim)

# Za pomocą funkcji size, sprawdź z ilu elementów składa się tablica b.

# print(b.size)

# Wybierz wartości dwa i cztery z tablicy b.

# print(b[0, 1])
# print(b[0, 3])

# Wybierz wszystkie wiersze z kolumny pierwszej tablicy b.

# print(b[:, 0])

# Wygeneruj macierz losową o rozmiarze 20 × 7, złożoną liczb całkowitych
#  w przedziale od 0 do 100. Wyświetl wszystkie wiersze dla czterech
# pierwszych kolumn

arr = np.random.randint(0, 101, size=(20,7))

# print(arr[:, [0,1,2,3]])
# print(arr[:, :4])

# DZIALANIA MATEMATYCZNE I LOGICZNE

# Stwórz dwie macierze liczb całkowitych z przedziału od 1 do 10 o
# rozmiarach 3 × 3 (a i b).

a = np.random.randint(1, 11, size=(3, 3))
b = np.random.randint(1, 11, size=(3, 3))

# Dodaj (za pomocą + oraz funkcii add)

a + b
np.add(a, b)

# odejmij (za pomocą - oraz funkcii subtract),

a - b
np.subtract(a, b)

# pomnóż (za pomocą * oraz funkcii multiply, dot, matmul)

a * b
np.multiply(a, b)

np.dot(a, b)

np.matmul(a, b)

# podziel (za pomocą / oraz funkcii divide)

a / b
np.divide(a, b)

# spotęguj (za pomocą ** oraz funkcii power)

a ** b
np.power(a, b)

# Sprawdź czy wartości macierzy a są większe lub równe 4.

a >= 4

# Sprawdź czy wartości macierzy a są większe bądź równe 1 i mniejsze
# bądź równe 4.

(a >= 1) & (a <= 4)

# Znajdź funkcję w numpy do obliczenia sumy głównej przekątnej macierzy b.

np.trace(b)

# DANE STATYSTYCZNE

# Oblicz sumę, wartość minimum, maksimum, odchylenie standardowe
# macierzy b.

np.sum(b)
np.min(b)
np.max(b)
np.std(b)

# Oblicz średnią dla wierszy w macierzy b.

np.mean(b, axis=1)

# Oblicz średnią dla kolumn macierzy b.

np.mean(b, axis=0)

# RZUTOWANIE WYMIAROW ZA POMOCA REHAPE LUB RESIZE

# Utwórz tablicę składającą się z 50 liczb (np., za pomocą funkcji arange).

arr = np.arange(50)

# Za pomocą funkcji reshape utwórz z tej tablicy macierz o wymiarach
# 10 × 5.

arr.reshape((10, 5))

# Zrób to samo za pomocą funkcji resize.

np.resize(arr, (10, 5))

# Sprawdź do czego służy komenda ravel. Napisz wniosek.

np.ravel(arr)

# print(arr)
# Komenda ravel "splaszcza" tablice wielowymiarowe do jednowymiarowej.

# Stwórz dwie tablice o rozmiarach 5 i 4 (np., za pomocą funkcji arange)
# i dodaj je do siebie. W tym celu sprawdź do czego służy funkcja
# newaxis i wykorzystaj ją. Napisz wniosek.

a = np.arange(5)
b = np.arange(4)

# print(a[:, np.newaxis] + b)

# Funkcja newaxis dodaje nowy wymiar do tablicy (tutaj z 1D zrobilismy 2D) i
# umożliwiło to dodawanie

# SORTOWANIE DANYCH

a = np.random.randint(0, 100, size=(5,5))

# Posortuj wiersze rosnąco

a.sort(axis=1)

# Posortuj kolumny malejąco.

a = np.sort(a, axis=0)[::-1]

# print(a)

# Posortuj dane rosnąco po kolumnie 2.

b=np.array([(1,"MZ","mazowieckie"), (2,"ZP","zachodniopomorskie"), (3,"ML","małopolskie")])

# Posortuj dane rosnąco po kolumnie 2.

sorted_indices = np.argsort(b[:, 1])
b = b[sorted_indices]

# print(b)

# Wyświetl nazwę województwa Zachodniopomorskiego.

# print(b[np.where(b[:,1] == "ZP"), 2][0][0])

# ZADANIA PODSUMOWUJACE

# 1. Utwórz macierz składającą się z pięciu kolumn i 10 wierszy losowo wybranych
#  liczb całkowitych z zakresu od 0 do 100 i policz sumę głównej
# przekątnej tej macierzy, używając funkcji trace a następnie wyświetl
# wartości używając funkcji diag.

arr = np.random.randint(0, 101, size=(10,5))

# print(np.trace(arr))
# print(np.diag(arr))

# 2. Utwórz dwie tablice wymiaru 5 × 5 z losowo wybranych liczb dziesiętnych z
# rozkładu normalnego i przemnóż je przez siebie.

arr1 = np.random.normal(0,1, size=(5,5))
arr2 = np.random.normal(0,1, size=(5,5))

# print(np.multiply(arr1,arr2))

# 3. Utwórz dwie tablice z losowo wybranych liczb całkowitych w zakresie
# od 1 do 100. Stwórz z nich macierze o 5 kolumnach i dodaj te macierze
# do siebie.

arr1 = np.random.randint(0, 101, 25)
arr2 = np.random.randint(0, 101, 25)

arr1 = arr1.reshape((5,5))
arr2 = arr2.reshape((5,5))

# print(np.add(arr1, arr2))

# 4. Stwórz dwie macierzy: jedną o 5 kolumnach i 4 wierszach oraz drugą o
# 4 kolumnach i 5 wierszach. Dodaj je do siebie używając transformacji
# wymiarów za pomocą jednego ze znanych sposobów.

arr1 = np.random.random(size=(4,5))
arr2 = np.random.random(size=(5,4))

arr1 = np.transpose(arr1)

# print(np.add(arr1, arr2))

# 5. Pomnóż kolumny 3 i 4, stworzonych przez siebie macierzy.

# print(np.multiply(arr1[:, 2], arr2[:, 3]))

# 6. Wygeneruj dwie macierze o rozkładzie normalnym (np.random.normal)
# i jednostajnym(np.random.uniform).
# Policz wartości średnie, odchylenie standardowe, wariancje,
# sumy, wartości minimalne i maksymalne. Wyniki wyświetl.

arr1 = np.random.normal(0,1, size=(5,5))
arr2 = np.random.uniform(0,1, size=(5,5))

# print(np.mean(arr1), np.std(arr1), np.var(arr1), np.sum(arr1), np.min(arr1), np.max(arr1))
# print(np.mean(arr2), np.std(arr2), np.var(arr2), np.sum(arr2), np.min(arr2), np.max(arr2))

# 7. Wygeneruj dwie macierze kwadratowe a i b (o wymiarach zdecyduj
# się samodzielnie), pomnóż je przez siebie używając (a*b) oraz funkcji
# dot. zobacz Jaka jest różnica? Napisz kiedy warto wykorzystać funkcję
# dot?

a = np.random.randint(0, 101, size=(5,5))
b = np.random.randint(0, 101, size=(5,5))

# print(a * b)
# print(np.dot(a, b))

# a * b dokonuje mnozenia po elementach np. a[i][j] * b[i][j] i to jest nasz wynik, a
# dot mnozy macierze w sposob algebraiczny

# 8. Sprawdź funkcję strides oraz as_strided. Zastosuj je do wyboru
# danych z macierzy np. 5 kolumn z trzech pierwszych wierszy.

arr = np.arange(25).reshape(5,5)

shape = (3, 5)
strides = arr.strides

view = np.lib.stride_tricks.as_strided(arr, shape=shape, strides=strides)

# print(view)

# 9. Wygeneruj dwie tablice a i b.
# Połącz je z użyciem funkcji vstack i stack. Czym one się różnią?
# Zastanów się i napisz, w jakich przypadkach warto je zastosować?

a = np.random.randint(0, 101, size=(3,3))
b = np.random.randint(0, 101, size=(3,3))

# print(np.vstack((a,b)))
# print(np.stack((a,b)))

# vstack doslownie skleja tablice w pionie. Mozemy to wykorzystac do laczenia kilku
# tablic w wiekszy zbior danych. stack natomiast pozwala na wieksza swobode, gdyz
# mozemy wybrac w jakim wymiarze bedzie to laczenie.

# 10. Użyj funkcji strides oraz as strided do obliczenia wartości maksymalnej
# bloków danych z macierzy (zob. rysunek)

arr = np.arange(24).reshape(4,6)

# print(arr)

shape = (2, 3)
strides = arr.strides

top_left = np.lib.stride_tricks.as_strided(arr, shape=shape, strides=strides)
top_right = np.lib.stride_tricks.as_strided(arr[:, 3:], shape=shape, strides=strides)
bottom_left = np.lib.stride_tricks.as_strided(arr[2:], shape=shape, strides=strides)
bottom_right = np.lib.stride_tricks.as_strided(arr[2:, 3:], shape=shape, strides=strides)

print(np.max(top_left), np.max(top_right), np.max(bottom_left), np.max(bottom_right))