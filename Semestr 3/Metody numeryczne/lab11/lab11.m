clc
close all
clear all

xg = [0,24,45,60,75,90,100,120,140,150];
yg = [0,30,25,8,15,20,17,20,30,0];

xd = [0,25,50,80,100,120,150];
yd = [0,-30,-15,-7,-15,-40,0];

fg = griddedInterpolant(xg,yg,'spline');
fd = griddedInterpolant(xd,yd,'spline');

x = linspace(0,150,1000);

h = 20;

calka1 = calka(fg,0,150,h);
calka2 = calka(fd,0,150,h);

pole = calka1 - calka2

hold on
plot(x,fg(x),'r',x,fd(x),'r',xg,yg,'blue*',xd,yd,'blue*')
