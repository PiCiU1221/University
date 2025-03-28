clc
close all
clear all

% ZAD 1

x = linspace(0,6,1000);

fp = @(x) -sin(2*x) * 2;
d = fp(x);

f = @(x) cos(2*x);

fcs = {@(x,h) (f(x+h)-f(x)/h)};
ftr = {@(x,h) ((f(x+h)-f(x-h))/(2*h))};
fpi = {@(x,h) ((-f(x+2*h)+8*f(x+h)-8*f(x-h)+f(x-2*h))/(12*h))};

h = [1, 0.5, 0.25];

figure

for i=1:length(fcs)
    for j=1:length(h)
        p = fcs{i}(x,h(j));
        mse = 1/length(d)*sum((d-p).^2);
        subplot(3,3,i+j-1)
        plot(x,d,x,p);
        title(['2pkt: h = ', num2str(h(j)),' blad: ', num2str(mse)])
    end

    for j=1:length(h)
        p = ftr{i}(x,h(j));
        mse = 1/length(d)*sum((d-p).^2);
        subplot(3,3,i+j+2)
        plot(x,d,x,p);
        title(['3pkt: h = ', num2str(h(j)),' blad: ', num2str(mse)])
    end

    for j=1:length(h)
        p = fpi{i}(x,h(j));
        mse = 1/length(d)*sum((d-p).^2);
        subplot(3,3,i+j+5)
        plot(x,d,x,p);
        title(['5pkt: h = ', num2str(h(j)),' blad: ', num2str(mse)])
    end
end


% ZAD 2

x = linspace(0,4,1000);

fp = @(x) cos(x) - 2*sin(2*x);
d = fp(x);

f = @(x) sin(x) + cos(2*x);

fwp = {@(x,h) ((-3*f(x)+4*f(x+h)-f(x+2*h))/(2*h))};
fce = {@(x,h) ((f(x+h)-f(x-h))/(2*h))};
fws = {@(x,h) ((f(x-2*h)-4*f(x-h)+3*f(x))/(2*h))};

h = [0.5, 0.25, 0.125];

figure

for i=1:length(fwp)
    for j=1:length(h)
        p = fwp{i}(x,h(j));
        mse = 1/length(d)*sum((d-p).^2);
        subplot(3,3,i+j-1)
        plot(x,d,x,p);
        title(['wprzod: h = ', num2str(h(j)),' blad: ', num2str(mse)])
    end

    for j=1:length(h)
        p = fce{i}(x,h(j));
        mse = 1/length(d)*sum((d-p).^2);
        subplot(3,3,i+j+2)
        plot(x,d,x,p);
        title(['centralny: h = ', num2str(h(j)),' blad: ', num2str(mse)])
    end

    for j=1:length(h)
        p = fws{i}(x,h(j));
        mse = 1/length(d)*sum((d-p).^2);
        subplot(3,3,i+j+5)
        plot(x,d,x,p);
        title(['wstecz: h = ', num2str(h(j)),' blad: ', num2str(mse)])
    end
end

% ZAD 3

x = linspace(0,5,1000);

fp = @(x) -16*cos(4*x);
d = fp(x);

f = @(x) cos(4*x) - (1/2)*x;

ftr = {@(x,h) ((f(x+h)-2*f(x)+f(x-h))/(h*h))};
fpi = {@(x,h) ((-f(x+2*h)+16*f(x+h)-30*f(x)+16*f(x-h)-f(x-2*h))/(12*h*h))};

h = [1, 0.5, 0.25];

figure

for i=1:length(ftr)
    for j=1:length(h)
        p = ftr{i}(x,h(j));
        mse = 1/length(d)*sum((d-p).^2);
        subplot(2,3,i+j-1)
        plot(x,d,x,p);
        title(['3pkt: h = ', num2str(h(j)),' blad: ', num2str(mse)])
    end

    for j=1:length(h)
        p = fpi{i}(x,h(j));
        mse = 1/length(d)*sum((d-p).^2);
        subplot(2,3,i+j+2)
        plot(x,d,x,p);
        title(['5pkt: h = ', num2str(h(j)),' blad: ', num2str(mse)])
    end
end