% LAB 01

% zad 1

x = [-3.0 -2.5 -2.0 -1.5 -1.0 -0.5 0 0.5 1.0 1.5 2.0 2.5 3.0];
y = [-0.25 -0.5 -0.75 -0.45 0.25 0 0.25 0.5 0.25 0 -0.25 -0.5 -0.25];

% zad 2

x_test = 0.25;
disp("zad 2 -- wartosc dla podanego punktu:")
y_test = 0.45

y1 = interp1(x, y, x_test, 'nearest');
y2 = interp1(x, y, x_test, 'linear');
y3 = interp1(x, y, x_test, 'spline');
y4 = interp1(x, y, x_test, 'cubic');

err1 = abs(y_test - y1)
err2 = abs(y_test - y2)
err3 = abs(y_test - y3)
err4 = abs(y_test - y4)
disp("zad 2 -- dla wskazanego punktu najlepiej wypadla metoda: spline")

% zad 3

xx = linspace(-3,3, 1000);

y1 = interp1(x, y, xx, 'nearest');
y2 = interp1(x, y, xx, 'linear');
y3 = interp1(x, y, xx, 'spline');
y4 = interp1(x, y, xx, 'cubic');

figure
hold on
plot(xx, y1)
plot(xx, y2)
plot(xx, y3)
plot(xx, y4)
plot(x, y, 'ro')
legend('nearest', 'linear', 'spline', 'cubic', 'punkty')
disp("zad 3 -- najlepiej wypadla metoda: spline")

% zad 4

figure
for i = 1:12
    p = polyfit(x, y, i);
    y5 = polyval(p, xx);
    subplot(3, 4, i)
    hold on
    plot(xx, y5)
    plot(x, y, 'ro')
    title(num2str(i))
end

disp("zad 4 -- najlepsze dopasowanie uzyskano dla wielomianu stopnia: 11")

% zad 5

p = polyfit(x, y, 11);
y5 = polyval(p, x_test);
err5 = abs(y_test - y5)
disp("zad 5 -- najlepsza metoda to: spline")