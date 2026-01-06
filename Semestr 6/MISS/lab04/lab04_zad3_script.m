clear all
close all
clc

out = sim("lab04_zad3");
x = out.x;
y = out.y;
R = str2num(get_param('lab04_zad3/Subsystem', 'R'));
rs = str2num(get_param('lab04_zad3/Subsystem', 'Rs'));

figure
for t = 1:length(x)
    clf
    daspect([1, 1, 1])

    rectangle(Position=[0-R,0-R,2*R,2*R], Curvature=[1, 1])
    rectangle(Position=[x(t)-rs,y(t)-rs,2*rs,2*rs], Curvature=[1, 1])

    axis([-10, 10, -10, 10])
    pause(2^-7)
end