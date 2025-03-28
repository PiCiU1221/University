clc
close all
clear all

wybor = 1;

switch wybor
    case 1
        f = @(x) cos(x);
        a = 0;
        b = 2;
    case 2
        f = @(x) 2.^(-x)+ exp(x) +2*cos(x) - 6;
        a = 1;
        b = 3;
    otherwise
        f = @(x) (x+2).^(5);
        a = -3;
        b = 0;
end

tol = 10^(-5);
ftol = 10^(-4);

tic
[xb, nb] = bisekcja(f, a, b, tol, ftol)
toc

tic
[xf, nf] = falsi(f, a, b, tol, ftol)
toc

t = a:0.01:b;
plot(t, f(t))
hold on;
plot(xb, f(xb), 'ro')
plot(xf, f(xf), 'rx')