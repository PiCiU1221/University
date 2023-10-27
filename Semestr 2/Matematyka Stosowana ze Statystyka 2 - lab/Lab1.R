# Lab1

# ZAD 1 
# a)

((2*3^3)/(sin(pi/6)))+log(2401, 7)

# b)

abs(-9+5^(-3))+((2^(1/3))^(1/5))

# c)

2^(1/3)*log(3^5+5^2-12,2) + (3+(7^(4/3)))^(1/5)

# ZAD 2

A = matrix(c(1,-10,12,3,2,1,-8,4,5), 3,3)
# wprowadzamy kolumnami
B = matrix(c(1,3,-1,2,1,5), 3,2)

# a)
# wyznacznik

det(A)

# b)
# macierz odwrotna oraz transponowana

solve(t(A))

# c)
# iloczyn macierzy AB, AA^transponowana, A^2

A %*% B

A %*% t(A)

A %*% A

# d)
# elementy po pomnozeniu pierwszego wiersza
# macierzy A oraz drugiej kolumny macierzy B

A[1,] * B[,2]


# ZAD 3
# NA KOLOKWIUM

C = matrix(c(1,2,5,-2,1,2,5,-3,-1,0,2,1,-2,3,5,2),4,4)

D = matrix(c(-7,21,40,2),4,1)

solve(C,D)

# podaj wartosc elementu w drugim wierszu i trzeciej
# kolumnie macierzy odwrotnej do macierzy ukladu
solve(C)[2,3]

solve(C)

# ZAD 4
# skonstruowac wektor w kwadratow liczb od 1 do 100
# a nastepnie zliczyc, ktore cyfry oraaz jak czesto
# wystepuja na pozycji jednosci w wyznaczonych
# kwadratach (uzyc operatora modulo,funkcji summary
# oraz typu factor). Ile wsrod kwadratow liczb od 1
# do 100 jest podzielnych przez 2, przez 3 oraz przez
# 2 i 3

w = (1:100)^2

summary(factor(w%%10))

summary(factor(w%%2 == 0))

summary(factor(w%%3 == 0))

summary(factor(w%%2 == 0 & w%%3 == 0))

# ZAD 5
# skonstruowac wektor w trzecich poteg wielokrotnosci
# liczby 7 od 21 do 903 nastepnie zlilczyc, ile wsrod
# elementow tego wektora jest liczb podzielnych przez
# 3, przez 11 oraz przez 3 i 11?
# NA KOLOKWIUM

w = seq(21,903,by = 7)^3

summary(factor(w%%3 == 0))

summary(factor(w%%11 == 0))

summary(factor(w%%3 == 0 & w%%11 == 0))

# ZAD 6
# zbudowac tablice trygonometryczne jako ramke danych,
# w ktorej zebrane beda informacje o wartosciach
# funkcji sinus, cosinus, tangens i cotangens dla
# katow: 0, 30, 45, 60, 90 (funkcje trygonometryczne
# w R przyjmuja argumenty w radianach). W tym celu napisaæ
# funkcjê rad (u¿yj function), która zamieni stopnie na
# radiany (sta³a pi w R ma oznaczenie pi), utworzyæ wektor
# w radianach oraz ramkê danych Tablice (u¿yæ
# data.frame).

rad = function(x) {x*pi/180}

x = c(0,30,45,60,90)
y = rad(x)

Tablice = data.frame(stopnie=x,sin(y),cos(y),tan(y),
                     ctg=1/tan(y))

# ZAD 7
# NIE ZROBIONE

G = matrix(c(-9,15,-14,-1,13,5,18,6,8,12,10,-4,-1,5,8,12),4,4)

H = matrix(c(4,298,294,120),4,1)

solve(G,H)

# Podaæ wartoœæ elementu w pierwszym wierszu
# i czwartej kolumnie macierzy odwrotnej do macierzy
# ukladu.
solve(G)[1,4]

solve(G)
