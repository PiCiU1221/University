clear all
close all
clc

out = sim("lab06");
x = out.x;
y = out.y;
r = out.r;
m1 = str2num(get_param('lab06/Subsystem','m1'));
m2 = str2num(get_param('lab06/Subsystem','m2'));
M = str2num(get_param('lab06/Subsystem','M'));

ltotal = 2*r(1);
for t = 1 : length(x)
    yc = -(ltotal - r(t));
    plot(x(t), y(t), 'k.', MarkerSize=20*m1) % kulka
    hold on
    plot(0, 0, 'b.', MarkerSize=20*M) % bloczek 1
    plot([0 x(t)], [0 y(t)], LineWidth=2) % lina bloczek 1 -> kulka
    plot(-1, 0, 'b.', MarkerSize=20*M) % bloczek 2
    plot([-1, 0], [0, 0], LineWidth=2) % linia bloczek 2 -> bloczek 1
    plot(-1, yc, 'k.', MarkerSize=20*m2) % ciezarek
    plot([-1, -1], [0 yc], LineWidth=2) % linia bloczek 2 -> ciezarek
    hold off
    axis([-6, 6, -6, 6])
    pause(2^-5)
end