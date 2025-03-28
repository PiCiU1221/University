% ZAD 2

clc
close all
clear all

p=[5,10,15];

for m=1:3
x = linspace(-3,3,p(m))';
y = abs(x);

V=[];

for i=1:length(x)
    for j=1:length(x)
        V(i,j) = x(i).^(j-1);
    end
end

a = V \ y;

X = linspace(-3,3,1000);
Y = 0;

for i=1:length(a)
    Y = Y + a(i)*X.^(i-1);
end

figure(p(m))
plot(X,Y,x,y,'k*')

end

% Na krancach przedzialow mozna zaobserwowac
% efekt Rungego.

% Aby uniknac tego efektu mozna gesciej upchac
% punkty przy krancach przedzialu interpolacji