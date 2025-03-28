function [] = lab14()
clc
close
clearvars

wybor = 5;

switch wybor
    case 1
        f = @(x1,x2) (x1.^2) + (x2.^2);
        x1p = -10;
        x1k = 10;
        x2p = -10;
        x2k = 10;
        x10 = 8;
        x20 = -10;
        krok = 1;
    case 2
        f = @(x1,x2) -cos(x1) .* cos(x2) .* exp(-((x1-pi).^2 + (x2-pi).^2));
        x1p = 2;
        x1k = 4;
        x2p = 2;
        x2k = 4;
        x10 = 2;
        x20 = 2;
        krok = 0.1;
    case 3
        f = @(x1,x2) (1-(8.*x1)+(7.*(x1.^2))-((7/3).*(x1.^3)) + ((1/4)*(x1.^4))) .* ((x2.^2) .* exp(-x2));
        x1p = 0;
        x1k = 5;
        x2p = 0;
        x2k = 5;
        x10 = 5;
        x20 = 5;
        krok = 0.2;
    case 4
        f=@(x1,x2) (1-x1).^2+100*(x2-x1.^2).^2;
        x1p=-2;
        x1k=2;
        x2p=-1;
        x2k=4;
        x10=-2;
        x20=3;
        krok=1;
    otherwise
        f=@(x1,x2) -cos(x1).*cos(x2).*exp(-((x1-pi).^2+(x2-pi).^2));
        x1p=1;
        x1k=5;
        x2p=1;
        x2k=5;
        x10=1.5;
        x20=5;
        krok = 0.5;
end

eps = 10^(-4);
[x1,y2,dx1,dx2,it] = sww(f,x10,x20,krok,eps,x1p,x1k,x2p,x2k);

subplot(2,1,1)

[x,y]=meshgrid(linspace(x1p,x1k),linspace(x2p,x2k));
mesh(x,y,f(x,y));
hold on

subplot(2,1,2);
z=f(x,y);
[c,h]=contour(x,y,z);
clabel(c,h);
hold on

plot(dx1(1),dx2(1), 'r*');
text(dx1(1),dx2(1), 'START');

plot(dx1(size(dx1)),dx2(size(dx2)), 'r*');
text(dx1(size(dx1)),dx2(size(dx2)), 'STOP');

line(dx1,dx2,'Color','k','Linewidth',1);

for i=1:length(dx1)-1
    contour(x,y,z,[f(dx1(i),dx2(i)),f(dx1(i),dx2(i))]);
end

it

end

function [x1,x2,dx1,dx2,it] = sww(f,x10,x20,krok,eps,x1p,x1k,x2p,x2k)
    e = [1 0 -1 0
        0 1 0 -1];
    dx1 = [x10];
    dx2 = [x20];
    fx = zeros(1,size(e,2));
    f0 = f(x10,x20);

    it = 1;

    while true
        
        for i = 1:size(e,2)
            fx(i) = f(x10 + e(1,i)*krok, x20 + e(2,i)*krok);
        end

        [f1, i] = min(fx);

        if f0 < f1
            x1 = x10;
            x2 = x20;

            break;
        end

        f0 = f1;
        x10 = x10 + e(1,i)*krok;
        x20 = x20 + e(2,i)*krok;
        dx1(end+1) = x10;
        dx2(end+1) = x20;
        
        it = it + 1;
    end
end