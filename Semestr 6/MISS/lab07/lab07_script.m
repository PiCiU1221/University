clear all
close all
clc

out = sim("lab07");
fi1 = out.fi1;
fi2 = out.fi2;
L1 = str2num(get_param('lab07/Subsystem','L1'));
L2 = str2num(get_param('lab07/Subsystem','L2'));
m1 = str2num(get_param('lab07/Subsystem','m1'));
m2 = str2num(get_param('lab07/Subsystem','m2'));


L = L1 + L2;
for t = 1 : length(fi1)
    x1 = -L1 * sin(fi1(t));
    y1 = -L1 * cos(fi1(t));
    x2 = -L2 * sin(fi2(t)) + x1;
    y2 = -L2 * cos(fi2(t)) + y1;

    plot(x1, y1, 'b.', MarkerSize = 20 * m1)
    hold on
    plot([0, x1], [0, y1], LineWidth= 2)

    plot(x2, y2, 'b.', MarkerSize = 20 * m2)
    hold on
    plot([x1, x2], [y1, y2], LineWidth= 2)

    hold off
    axis([-1.1 * L, 1.1 * L, -1.1 * L, 1.1 * L])
    pause(2^-5)
end