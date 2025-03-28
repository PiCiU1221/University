clc
close all
clearvars

A = [3,2,1;5,4,3;1,1,0];
b = [120;300;50];
c = [12;8;10];

tol = 10^(-8);

[x,f] = lab20funkcja(A,b,-c,tol);

x