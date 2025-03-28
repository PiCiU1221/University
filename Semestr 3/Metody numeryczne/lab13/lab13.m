clc
close all
clear all

wybor = 3;

switch wybor
    case 1
        f = @(x) x.^2 - x;
        a = 0.25;
        b = 0.75;
    case 2
        f = @(x) (1/3)*x.^2 - (13/7)*x + 11;
        a = -10;
        b = 10;
    case 3
        f = @(x) x.^4 - 12*x.^3 + x + 4;
        a = -2;
        b = 2;
    otherwise
        f = @(x) -x.^3 + 3*x.^2 - 3*x;
        a = -2;
        b = -1;    
end

eps = 1e-4;

tic
[x1, n1] = metoda_polowienia(f, a, b, eps);
n1
toc

tic
[x2, n2] = metoda_newtona(f, a, b, eps);
n2
toc

t = a:0.01:b;
plot(t, f(t))
hold on;
plot(x1, f(x1), 'ro')
plot(x2, f(x2), 'rx')