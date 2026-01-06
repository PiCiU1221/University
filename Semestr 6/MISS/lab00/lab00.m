% zad 1
f1 = @(x) sin(x) + cos(x);
f2 = @(x) exp(x) + log(x);
f3 = @(x, y) sin(x) .* cos(y);

% zad 2
x = linspace(0.1, 4, 1000);
plot(x, f1(x))
hold on
plot(x, f2(x))
legend('sin(x) + cos(x)', 'exp(x) + log(x)')

% zad 3
figure
x = linspace(-2*pi, 2*pi, 100);
y = linspace(-2*pi, 2*pi, 100);
[X, Y] = meshgrid(x, y);
surf(X, Y, f3(X, Y))

% zad 4
% x * (max - min) + min
x = rand(1, 7) * 3 + 2;
y = rand(1, 7) * 4 + 3;

func1(x, y)

function func1(x, y)
    figure
    plot(x, y, 'rs', MarkerSize = 15)
    hold on
    plot(x, y, 'k--', LineWidth = 3)
end