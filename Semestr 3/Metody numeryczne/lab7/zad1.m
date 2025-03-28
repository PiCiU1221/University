% ZAD 1

clc
close all
clear all

xg = [0,10,20,90,120,200,260,265,270];
yg = [35,40,45,50,70,70,50,40,25];

xd = [0,40,60,80,190,210,230,260,270];
yd = [35,15,0,15,15,0,15,15,25];

x1 = linspace(0,max(xg), 1000);
x2 = linspace(0,max(xd), 1000);

cos = interp1(xg,yg,x1,'linear');
cos2 = interp1(xd,yd,x2,'linear');
subplot(2,2,1);
plot(xg,yg,'k*',x1,cos,'r',xd,yd,'k*',x2,cos2,'b');
daspect([1,1,1]);

cos21 = interp1(xg,yg,x1,'nearest');
cos22 = interp1(xd,yd,x2,'nearest');
subplot(2,2,2);
plot(xg,yg,'k*',x1,cos21,'r',xd,yd,'k*',x2,cos22,'b');
daspect([1,1,1]);

cos31 = interp1(xg,yg,x1,'pchip');
cos32 = interp1(xd,yd,x2,'pchip');
subplot(2,2,3);
plot(xg,yg,'k*',x1,cos31,'r',xd,yd,'k*',x2,cos32,'b');
daspect([1,1,1]);

cos41 = interp1(xg,yg,x1,'spline');
cos42 = interp1(xd,yd,x2,'spline');
subplot(2,2,4);
plot(xg,yg,'k*',x1,cos41,'r',xd,yd,'k*',x2,cos42,'b');
daspect([1,1,1]);