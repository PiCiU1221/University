# Lab4

# P(X <= a) = p => (a-m)/sig = qnorm(p)

# ZAD 1

# Wiek komputerów w pewnej firmie kszta³tuje siê zgodnie
# z rozk³adem normalnym.Ustaliæ prawdopodobieñstwo
# wylosowania komputera, który ma od 3 do 6 lat, przy
# za³o¿eniu, ¿e:
# a) wœród 200 komputerów 100 ma powy¿ej 5 lat, a
# sig =1;
# b) prawdopodobieñstwo wylosowania komputera, który
# ma poni¿ej 6 lat wynosi 0.6 a sig^2 = 4.


# X - wiek komputerow

# P(3 <= X <= 6) = ?

# a) 

# P(X > 5) = 0.5
# P(X <= 5) = 0.5

sig = 1

# (5-m)/sig = qnorm(0.5) /* sig
# 5-m = qnorm(0.5) * sig
# m = 5 - sig * qnorm(0.5)

pnorm(6,m,sig) - pnorm(3,m,sig)

# b) 

# P(X < 6) = 0.6
sig = 2

# (6 - m)/sig = qnorm(0.6)

m = 6 - sig * qnorm(0.6)

pnorm(6,m,sig) - pnorm(3,m,sig)

# ZAD 2
# Przeciêtny wskaŸnik rentownoœci obrotu brutto
# podmiotów gospodarczych w sektorze publicznym
# wynosi 5.2%. Zak³adaj¹c, ¿e wskaŸnik ten mo¿na
# aproksymowaæ za pomoc¹ rozk³adu normalnego,
# obliczyæ wartoœæ odchylenia standardowego,
# wiedz¹c, ¿e 12.1% podmiotów gospodarczych osi¹ga
# wskaŸnik rentownoœci poni¿ej 3%. Okreœliæ wartoœæ
# kwantyla rzêdu 0.8.

# m = 5.2% = 5.2

# P(X < 3) = 12.1% = 0.121

# (3 - m)/ sig = qnorm(0.121)

m = 5.2
sig = (3 - m) / qnorm(0.121)

qnorm(0.8, m, sig)

# ZAD 3
# Wyk³adowca prowadz¹cy wyk³ad z matematyki
# stosowanej ze statystyk¹ II przychodzi do sali na
# ogó³ 5 minut przed wyznaczon¹ godzin¹ rozpoczêcia
# zajêæ. Zak³adaj¹c, ¿e czas przyjœcia jest zmienn¹
# losow¹ o rozk³adzie normalnym, okreœliæ, jakie jest
# prawdopodobieñstwo spóŸnienia siê tego wyk³adowcy
# na zajêcia, je¿eli wiadomo, ¿e w oko³o 95%
# przypadków wyk³adowca jest w sali co najmniej
# 3 minuty przed rozpoczêciem zajêæ.

m = -5

# P(X <= -3) = 0.95
# (-3 - m)/sig = qnorm(0.95)

sig = (-3 - m) / qnorm(0.95)

pnorm(0, m, sig, F)


# ZAD 4

m = 0.46

# P(X > 0.5) = 0.4

# (50 - m) / sig = 1 - qnorm(0.46)
# (50 - m) = (1 - qnorm(0.46)) * sig
# (50 - m) / (1 - qnorm(0.46)) = sig

sig = (0.5 - m) / qnorm(0.6)

# a) 
pnorm(0.7, m, sig, F)

# b)
qnorm(0.9, m, sig)

# ZAD 5

m = 86.5

# P(82.5 <= X <= 90.5) = 0.3472

# P(X <= 82.5) = (1 - 0.3472) / 2

# (82.5 - m) / sig = qnorm((1 - 0.3472) / 2)

sig = (82.5 - m) / qnorm((1 - 0.3472) / 2)

pnorm(95, m, sig, F) * 400
