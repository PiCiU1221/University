clear all
close all
clc

out = sim("lab05");
r = out.r;
th = out.th;
L = str2num(get_param('lab05/Subsystem', 'L'));
m = str2num(get_param('lab05/Subsystem', 'm'));

Lmax = (L + max(r));
for t = 1 : length(r)
    x = -(L + r(t)) * sin(th(t));
    y = -(L + r(t)) * cos(th(t));
    plot(x, y, 'b.', MarkerSize=m*5)
    hold on
    [xs, ys] = generate_spring(L, r(t), th(t), 0, 0);
    plot(xs, ys, LineWidth=2)
    hold off
    axis([-Lmax, Lmax, -Lmax, Lmax])
    pause(2^-6)
end

function [x, y] = generate_spring(L, r, theta, x_start, y_start)
    spring_length = L + r;    
    theta = -(theta) - pi/2; 
    amp = 0.1; % szerokosc sprezyny
    coil_number = 30; % gestosc
    
    
    x_spring = 0: 0.01 : (spring_length - 0.2); % 0.2 na zaczepienie
    x_coils = linspace(0, pi * coil_number, length(x_spring)); 
    % zmapowanie y dla sinusoidy na wsp. na linie wahadla
    coords = [x_spring, spring_length; sin(x_coils) * amp, 0];
    
    R = [cos(theta) -sin(theta); sin(theta) cos(theta)]; 
    rotcoord = R*coords;

    x = x_start + rotcoord(1, :);
    y = y_start + rotcoord(2, :);
end