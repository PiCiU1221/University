# Lab 5

# ZAD 1 
# Przeciêtne miesiêczne wynagrodzenie brutto w
# gospodarce narodowej w roku 2016 wynios³o 4001.50 z³.
# Wiadomo, ¿e 15% zatrudnionych w tej grupie osi¹ga
# zarobki od 3503 do 4500 z³. Przyjmuj¹c, ¿e rozk³ad
# p³ac jest normalny, obliczyæ jakiej wysokoœci
# pensje otrzymuje 25% najwiêcej zarabiaj¹cych w tym
# sektorze.

m = 4001.50

# P(3503 <= X <= 4500) = 15%

sig = (3503 - m) / qnorm((1 - 0.15) / 2)

qnorm(0.75, m, sig)

# ZAD 2
# Decyl trzeci miesiêcznego wynagrodzenia brutto
# w województwie zachodniopomorskim w paŸdzierniku
# 2018 roku w grupie przedstawicieli w³adz
# publicznych, wy¿szych urzêdników i kierowników
# wynosi³ 5281.21 z³ zaœ kwartyl górny 9090.90 z³.
# Przyjmuj¹c, ¿e rozk³ad p³ac jest normalny,
# wyznaczyæ
# a) procent pracowników zarabiaj¹cych mniej ni¿
# 3200 z³ brutto,
# b) procent pracowników zarabiaj¹cych ponad 7800 z³
# brutto,
# c) maksymalne wynagrodzenie brutto otrzymywane
# przez 15% pracowników najmniej zarabiaj¹cych
# w tym sektorze.

# A = [ 1 qnorm(p1)]    B = [ a1 ]
#     [ 1 qnorm(p2)]        [ a2 ]

# a) P(X <= 5281.21) = 0.3
#    P(X <= 9090.9) = 0.75

# (5282.21 - m) / sig = qnorm(0.3)
# (9090.9 - m) / sig = qnorm(0.75)

# m + sig * qnorm(0.3) = 5281.21
# m + sig * qnorm(0.75) = 9090.9

A = matrix(c(1,1,qnorm(0.3),qnorm(0.75)),2,2)
B = matrix(c(5281.21,9090.9),2,1)

m = solve (A,B) [1]
sig = solve (A,B) [2]

pnorm(3200, m, sig)

# b) 

pnorm(7800, m, sig, F)

# c)

qnorm(0.15, m, sig)


# ZAD 3
# Czas trwania zakupów dla 20% klientów sklepu
# Ikea wynosi ponad 2 godziny, a dla 44% poni¿ej
# 1.5 godz. Zak³adaj¹c, ¿e czas trwania zakupów
# mo¿na okreœliæ za pomoc¹ rozk³adu normalnego,
# wyznaczyæ:
# a) prawdopodobieñstwo spotkania klienta, którego
# czas pobytu w sklepie wynosi krócej ni¿ 0.5 godziny,
# b) procent klientów, którzy spêdzaj¹ w sklepie
# Ikea ponad 2.5 godziny,
# c) czas graniczny 13% klientów, którzy robi¹
# zakupy najd³u¿ej.

# P(X >= 2) = 0.2  (odwracamy gdy X >=)
# P(X <= 1.5) = 0.44

A = matrix(c(1,1,qnorm(0.8),qnorm(0.44)),2,2)
B = matrix(c(2,1.5),2,1)

m = solve (A,B) [1]
sig = solve (A,B) [2]

# a)
pnorm(0.5, m, sig)

# b)
pnorm(2.5, m, sig, F)

# c)
qnorm(0.87, m, sig)


# ZAD 4
# Œrednia wzrostu doros³ych kobiet w Polsce to
# oko³o 165 cm i wiadomo, ¿e oko³o 93 % kobiet
# mierzy co najmniej 155 cm i nie wiêcej ni¿ 175 cm.
# Wiedz¹c, ¿e wzrost kobiet ma rozk³ad normalny,
# okreœliæ ile kobiet wœród 500 bêdzie mierzyæ
# powy¿ej 170 cm.

m = 165

# P(155 =< X <= 175) = 0.93

# P(X >= 155)
# P(X <= 175)

sig = (155 - m) / qnorm((1 - 0.93) / 2)

# P(X >= 170) * 500 = ?

pnorm(170, m, sig, F) * 500

# ZAD 5
# Rozk³ad wyników kolokwium 1. z matematyki
# stosowanej ze statystyk¹ 2 na zajêciach
# laboratoryjnych z wykorzystaniem œrodowiska R
# mo¿na szacowaæ za pomoc¹ rozk³adu normalnego.
# Wynik bardzo dobry (ponad 90%) zwykle osi¹ga
# jedna osoba w grupie 12 studentów, natomiast
# 2 osoby na 12 nie zalicza w pierwszym terminie
# (nie osi¹ga 50%). Jaki minimalny wynik osi¹ga
# 10% najlepiej przygotowanych studentów?

# P(X >= 90) = 1/12
# P(X < 50) = 2/12

A = matrix(c(1,1,qnorm(11/12),qnorm(2/12)),2,2)
B = matrix(c(90,50),2,1)

m = solve (A,B) [1]
sig = solve (A,B) [2]

qnorm(0.90, m, sig) #88.27362

# ZAD 6
# Badania Pomorskiego Uniwersytetu Medycznego w
# Szczecinie wykaza³y, ¿e wiek pacjentów leczonych
# z powodu raka krtani ma rozk³ad normalny.
# W analizowanym okresie na 524 pacjentów tylko
# 2 by³o poni¿ej 17 roku ¿ycia oraz 7
# przekroczy³o 70 lat. Wyznaczyæ prawdopodobieñstwo,
# ¿e leczenia z powodu raka krtani wymagaæ bêd¹
# osoby w wieku od 45 do 55 lat.

# P(X <= 17) = 2/524
# P(X >= 70) = 7/524

A = matrix(c(1,1,qnorm(2/524),qnorm(517/524)),2,2)
B = matrix(c(17,70),2,1)

m = solve (A,B) [1]
sig = solve (A,B) [2]

# P(45 <= X <= 55) = ?

pnorm(55,m,sig) - pnorm(45,m,sig) #0.3327448