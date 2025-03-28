% Laboratorium 4 - Rachunek bledow

clc
close all
clear all

% ZAD 1
% format short;
% a = 0.2 + 0.2 + 0.2
% a = 0.6

% format long e;
% a = 0.2 + 0.2 + 0.2
% a = 0.6

% Komputer nie jest w stanie dokladnie obliczyc danego
% zadania w 100% dokładnie, gdyż jego działanie opiera
% się na potęgach liczby 2 i niektórych liczb nie da się
% przedstawić w skończonym formacie dla komputera i
% uzywa on przyblizeń. Dlatego na końcu zostało nam
% coś dodatkowego.

% 6.000000000000001e-01
% 6.000000000000000e-01

% ZAD 2

% format long e
% 
% x = [exp(1), -pi, sqrt(2), -psi(1), log10(2)];
% y = [1486.2497, 878366.9879, -22.37492, 4773714.647, 0.000185049];
% 
% % 1.
% wynik1 = x * y'
% 
% % 2.
% wynik2 = sum(x.*y)
% 
% % 3.
% wynik3 = 0;
% for i = 1:5
%     wynik3 = wynik3 + x(i)*y(i);
% end
% wynik3
% 
% % 4.
% wynik4 = 0;
% for i = 5:-1:1
%     wynik4 = wynik4 + x(i)*y(i);
% end
% wynik4
% 
% blad2 = abs(wynik1 - wynik2);
% blad3 = abs(wynik1 - wynik3);
% blad4 = abs(wynik1 - wynik4);
% 
% bar([blad2, blad3, blad4]);

% ZAD 3

% format long e;
% 
% x = 29/13
% y = 29 - 13*x
% x1 = 29/1300
% y1 = 29 - 1300*x1

% Dzieje się tak ponieważ w pierwszym przypadku
% mieliśmy 13 razy x ktory był stosunkowo duży i
% komputer sobie poradził bez problemu i podał
% prawidłowy wynik. W następnym przypadku x1 był
% na tyle mały i gdy został pomnożony przez 1300
% blad kalkulacji systemu dwojkowego był na tyle
% duży, że komputer nie był w stanie podać
% prawidłowego rezultatu.

% ZAD 4

% for k = 4:10
%     x = 10.^k;
%     a = sqrt(1+x.^2);
% 
%     w1 = x - a
%     w2 = -1/(x+a)
% end

% Tak, widać różnicę. Przy dużym k błąd jest na
% tyle duży, że wynik jest zaokrąglany do 0, a
% z single x i a wydaja sie identyczne i w1
% sie od razu zeruje.

% for k = 4:10
%     x = 10.^k;
%     x = single(x);
%     a = sqrt(1+x.^2);
% 
%     w1 = x - a
%     w2 = -1/(x+a)
% end

% ZAD 5

% d = 10^-3;
% x = linspace(2-d,2+d,1000);
% 
% a = (x-2);
% 
% f1 = @(x) a.^4;
% f2 = @(x) x.*x.*x.*x - 8.*x.*x.*x + 24.*x.*x - 32.*x + 16;
% 
% plot(x, f1(x), 'r')
% hold on
% plot(x, f2(x), 'g')
% 
% max = abs(f1(x)-f2(x));
% err = abs(f1(x)-f2(x));
% 
% figure
% plot(x, err, 'r');