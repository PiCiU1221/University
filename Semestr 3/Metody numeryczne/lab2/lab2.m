clc
close all
clear all

% f = @(x) 8*sin(x) - 2*x;
% g = @(x) abs(f(x));
% 
% x1 = linspace(0,10,100);
% x2 = linspace(0,10,20);

% ZAD 1
% plot(x1,f(x1), 'r')
% hold on
% plot(x2,g(x2), 'g.')
% 
% plot(x1,f(x1),'r', x2,g(x2), 'g.')
% title('Zadanie 1')
% xlabel('x')
% ylabel('y')
% legend('f(x)', 'g(x)')

% ZAD 2
% f = @(x) sin(x);
% g = @(x) round(x);
% 
% x1 = -5:0.5:5;
% x2 = -3:0.2:6;
% 
% subplot(1,2,1)
% plot(x1,f(x1),'r');
% subplot(1,2,2)
% plot(x2,g(x2), 'black');
% title('Zadanie 2')

% ZAD 3
% f = @(x) sin(x);
% 
% x1 = -5:0.1:5;
% 
% subplot(2,4,[1 2])
% plot(x1,f(x1),'blue');
% title('f(x) = sin(x)')
% 
% subplot(2,4,[3 4])
% f = @(x) cos(x);
% plot(x1,f(x1),'green');
% title('f(x) = cos(x)')
% 
% subplot(2,4,5)
% f = @(x) tan(x);
% plot(x1,f(x1), 'black');
% title('f(x) = tan(x)')
% 
% subplot(2,4,[6 7])
% f = @(x) abs(x);
% plot(x1,f(x1), 'red');
% title('f(x) = abs(x)')
% 
% subplot(2,4,8)
% f = @(x) x;
% plot(x1,f(x1),'magenta');
% title('f(x) = x')

% ZAD 4
% f = @(x) sin(x) + 0.2 * rand(size(x));
% x1 = -4:0.1:6;
% x2 = 2:0.01:4;
% 
% axes('Position',[0.1 0.1 0.7 0.7])
% plot(x1,f(x1))
% axes('Position',[0.63 0.63 0.3 0.3])
% plot(x2,f(x2))

% ZAD 5
% x = -10:0.5:10;
% y = -5:0.5:5;
% [X,Y] = meshgrid(x,y);
% Z = X.^2 + Y.^2;
% mesh(X,Y,Z)
% hold on
% plot3(0,0,0,'Marker','.','MarkerSize',50,'Color','r')

% ZAD 6
x1 = 200:500;
[X,Y] = meshgrid(x1,x1);
Z = 418.9829 * 2 - X.*sin(sqrt(abs(X))) - Y.*sin(sqrt(abs(Y)));
contour(X,Y,Z,'ShowText','on')

% ZAD 7
hold on
xp = [200, 300, 425, 420];
yp = [200, 225, 300, 420];