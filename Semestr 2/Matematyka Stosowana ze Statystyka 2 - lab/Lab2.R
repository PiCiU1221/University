# Lab2

# ZAD 1
# Prawdopodobieñstwo, ¿e statystyczny student nie jest
# przygotowany do æwiczeñ wynosi 1/3. Nauczyciel wybiera
# przypadkowo 4 osoby. Niech X oznacza liczbê osób
# spoœród wybranych, które nie s¹ przygotowane do
# æwiczeñ. Wyznaczyæ rozk³ad prawdopodobieñstwa
# tej zmiennej losowej. Obliczyæ prawdopodobieñstwo, ¿e:
# a) liczba osób nieprzygotowanych jest mniejsza ni¿ 2
# b) liczba osób nieprzygotowanych wynosi co najmniej 3.

# rozklad dwumianowy, n = 4, p = 1/3

x = c(0:4)

pr = dbinom(x,4,1/3)

rozklad = cbind(x,pr)

plot(x,pr)

# a)
# P(X < 2) = P(X <= 1)

pbinom(1,4,1/3)

# b)
# P(X >= 3) = 1 - P(X < 3) = 1 - P(X <= 2)

1 - pbinom(2,4,1/3)
pbinom(2,4,1/3,F)

# ZAD 2
# Niech X oznacza liczbê samochodów przeje¿d¿aj¹cych
# w ci¹gu minuty przez Plac Szarych Szeregów w
# Szczecinie. Zmienna ta mo¿e byæ opisana za pomoc¹
# rozk³adu Poissona z parametrem (intensywnoœci¹)
# lampda=12.
# 1) Obliczyæ prawdopodobieñstwo, ¿e w ci¹gu minuty
# przejedzie przez ten plac:
# a) dok³adnie 15 samochodów,
# b) od 7 do 13 samochodów.
# 2) Prawdopodobieñstwo, ¿e liczba samochodów
# przeje¿d¿aj¹cych przez ten plac w ci¹gu
# minuty jest nie wiêksza ni¿ k wynosi 0.96.
# Wyznaczyæ wartoœæ k.

# rozklad Poissona, lambda = 12

# 1) a) P(X = 15)
dpois(15,12)

# 1) b) P(7 <= X <= 13)
sum(dpois(c(7:13),12))

ppois(13,12) - ppois(6,12)

# 2) P(X <= k) = 0.96, k - kwantyl rzedu 0.96
qpois(0.96,12)

# ZAD 3
# Prawdopodobieñstwo awarii aparatury doœwiadczalnej
# w jednym doœwiadczeniu wynosi 0.02. Doœwiadczenia
# mo¿na przeprowadzaæ dowoln¹ liczbê razy. Obliczyæ
# prawdopodobieñstwo, ¿e pierwsza awaria zdarzy siê:
# a) w czwartym doœwiadczeniu,
# b) nie póŸniej ni¿ w trzecim doœwiadczeniu.

# rozklad geometryczny, p = 0.02
# (zawsze jeden mniej)
# a) P(X = 3)
dgeom(3,0.02)

# b) P(X <= 2)
sum(dgeom(c(0:2),0.02))

pgeom(2,0.02)

# ZAD 4
# W sk³ad pewnego agregatu wchodzi 100 elementów
# okreœlonego rodzaju.Prawdopodobieñstwo uszkodzenia
# w ci¹gu roku ka¿dego z tych elementów wynosi 0.01
# i nie zale¿y od stanu pozosta³ych. Obliczyæ
# prawdopodobieñstwo uszkodzenia w ci¹gu roku:
# a) dok³adnie dwóch elementów,
# b) nie wiêcej ni¿ dwóch elementów.
# W obu podpunktach obliczyæ tak¿e przybli¿enie
# rozk³adem Poissona.

# a) P(X = 2) n = 100, p = 0.01

dbinom(2,100,0.01)

# rozklad poissona

dpois(2,100*0.01)

# b) P(X <= 2)

pbinom(2,100,0.01)

# rozklad poissona

ppois(2,100*0.01)

# ZAD 5
# W pewnej rodzinie dwoje spoœród czworga dzieci
# urodzi³o siê w niedzielê. Jakie jest
# prawdopodobieñstwo tego zdarzenia?

# p = 1/7

dbinom(2,4,1/7)

# ZAD 6
# Urz¹dzenie sk³ada siê miêdzy innymi z 750 lamp.
# Prawdopodobieñstwo awarii ka¿dej lampy w ci¹gu
# jednej doby pracy urz¹dzenia jest jednakowe i
# wynosi 0.004. Obliczyæ prawdopodobieñstwo, ¿e w
# ci¹gu jednej doby pracy urz¹dzenia ulegn¹ awarii
# co najmniej 3 lampy.

# P ()

pbinom(2,750,0.004,F)

# ZAD 7
# W rodzinie jest dziesiêcioro dzieci. Przyjmuj¹c,
# ¿e prawdopodobieñstwo urodzenia siê ch³opca i
# dziewczynki jest równe obliczyæ prawdopodobieñstwo,
# ¿e w danej rodzinie jest:
# a) piêciu ch³opców,
# b) ch³opców nie mniej ni¿ trzech i nie wiêcej
# ni¿ oœmiu.

# p = 0.5, n = 10

dbinom(5,10,0.5)
# 0.2460938

sum(dbinom(c(3:8),10,0.5))
# 0.9345703

# ZAD 8
# Doœwiadczenie polega na rzucaniu dwiema kostkami
# do gry tak d³ugo, a¿ suma oczek wyniesie 3.
# Obliczyæ prawdopodobieñstwo zdarzeñ:
# a) trzeba bêdzie wykonaæ piêæ rzutów,
# b) suma oczek równa 3 nie pojawi siê w szeœciu
# kolejnych rzutach.

dgeom(4,1/18)
# 0.04420111

# P(X >= 6) = 1 - P(X <= 5)
pgeom(5,1/18,F)
# 0.7096734

# ZAD 10
# Hazardzista kontynuuje grê w ruletkê, obstawiaj¹c
# zawsze „czerwone”, a¿ uda mu siê w koñcu wygraæ.
# Zak³adaj¹c, ¿e prawdopodobieñstwo wypadniêcia pola
# czerwonego wynosi 18/38, a hazardzistê staæ jedynie
# na 5 zak³adów, oblicz prawdopodobieñstwo, ¿e: 
# a) uda mu siê wygraæ w drugim podejœciu,
# b) uda mu siê wygraæ, nim wyda pieni¹dze.

# a) P(X = 1)
dgeom(1,18/38)

# b) P(X <= 4)
pgeom(4,18/38)
