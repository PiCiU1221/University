clc
close all
clear all

x = [1,6,14,21];
y = [13,11,18,15];
X = linspace(min(x),max(x),1000);

a = wsp(x',y');

Y = wart(a,X,x);

plot(X,Y,x,y,'k*')

% temperatura o godz 1045
temp1045(X,Y)

% godzina z najwyzsza temperatura
najwyzsza(X,Y)

% taka sama temperatura jak o godz 13
taka_sama(X,Y)