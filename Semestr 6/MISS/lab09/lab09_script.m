close all
clc

out = sim("lab09");
h1 = out.h1;
h2 = out.h2;

S1 = str2num(get_param('lab09/Subsystem', 's1'));
S2 = str2num(get_param('lab09/Subsystem', 's2'));
Swy1 = str2num(get_param('lab09/Subsystem', 'swy1'));
Swy2 = str2num(get_param('lab09/Subsystem', 'swy2'));

for t = 1 : length(h1)
    plot([0 0], [0 max(h1)+1], 'k')
    hold on
    plot([0 S1+S2+2], [0, 0], 'k')
    plot([S1 S1], [Swy1 max(h1) + 1], 'k')
    plot([S1 S1+1], [Swy1 Swy1], 'k')
    plot([S1+1 S1+1], [Swy1 max(h2)+1], 'k')
    plot([S1+S2+1 S1+S2+1], [Swy2 max(h2) + 1], 'k')
    plot([S1+S2+1 S1+S2 + 2], [Swy2 Swy2], 'k')

    fill([0 S1 S1 0], [0 0 h1(t) h1(t)], 'b', EdgeColor = 'None')
    fill([S1 S1+1 S1+1 S1], [0 0 min(Swy1, h2(t)) min(Swy1, h1(t))], 'b', EdgeColor = 'None')

    fill([S1+1 S1+S2+1 S1+S2+1 S1+1], [0 0 h2(t) h2(t)], 'b', EdgeColor = 'None')
    fill([S1+S2+1 S1+S2+2 S1+S2+2 S1+S2+1], [0 0 min(Swy2, h2(t)) min(Swy2, h1(t))], 'b', EdgeColor = 'None')
    hold off

    axis([-1, S1+S2+3, -1, max(h1)+1])
    pause(0.05)
end
