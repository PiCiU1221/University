clc
close all
clear all

wybor = 2;

switch wybor
    case 1
        f = @(x) exp(x-1) - 2;
        a = -1;
        b = 2;
    case 2
        f = @(x) 2.^(-x)+ exp(x) +2*cos(x) - 6;
        a = 1;
        b = 3;
    case 3
        f = @(x) log(x+(2/3));
        a = -(1/2);
        b = 2;
    otherwise
        f = @(x) x.^(3) - (2 * x) - 5;
        a = 0;
        b = 3;
end

tol = 10^(-5);
ftol = 10^(-4);

tic
[xb, nb] = sieczne(f, a, b, tol, ftol)
toc

tic
[xf, nf] = styczne(f, a, b, tol, ftol)
toc

t = a:0.01:b;
plot(t, f(t))
hold on;

plot(xb, f(xb), 'ro')
plot(xf, f(xf), 'rx')