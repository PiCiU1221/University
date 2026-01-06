close all
clear all
clc

out = sim("lab08");
xw = out.x;
yw = out.y;

xm = str2num(get_param('lab08/Subsystem', 'xi'));
ym = str2num(get_param('lab08/Subsystem', 'yi'));
dm = str2num(get_param('lab08/Subsystem', 'di'));
am = str2num(get_param('lab08/Subsystem', 'ai'));
L = str2num(get_param('lab08/Subsystem', 'L'));
m = str2num(get_param('lab08/Subsystem', 'm'));

for t = 1:length(xw)
    plot3(xm(am > 0), ym(am > 0), dm(am > 0), 'r.', MarkerSize = 20)
    hold on
    plot3(xm(am < 0), ym(am < 0), dm(am < 0), 'b.', MarkerSize = 20)

    B = sqrt(xw(t)^2 + yw(t)^2);
    C = sqrt(L^2 - B^2);
    Z = L - C;
    plot3(xw(t), yw(t), Z, 'k.', MarkerSize=20*m)
    plot3([0 xw(t)], [0 yw(t)], [L Z], LineWidth = 2)
    hold off
    axis([-2, 2, -2, 2, -0.5, 4])
    pause(0.01)
end