clc
close all

wybor = 4;

switch wybor
    case 1
        f=@(x)x(1,:).^2 + x(2,:).^2;
        xp=-10;
        xk=10;
        yp=-10;
        yk=10;
        x0 = [-10;10];
        krok = 1;
    case 2
        f=@(x)3*x(1,:).^4 - 2/3*x(2,:).^3+2*x(1,:).^2.*x(2,:)-2*x(1,:).^2+x(2,:).^2;
        xp=-1;
        xk=0.4;
        yp=-1;
        yk=1;
        x0=[-1;1];
        krok = 0.1;
    case 3
        f=@(x)10*x(1,:).^2+15*x(2,:).^2+20*x(1,:).*x(2,:)+5*x(1,:)-20*x(2,:);
        xp=-8;
        xk=8;
        yp=-8;
        yk=8;
        x0=[8;-8];
        krok = 1;
    otherwise
        f=@(x) 100*(x(2,:)-x(1,:).^2).^2+(1-x(1,:)).^2;
        xp=-2;
        xk=2;
        yp=-1;
        yk=3;
        x0=[-2;3];
        krok = 0.5;
end
gtol = 1e-4;
ftol = 1e-4;

[x_opt, dx, it] = metodaGradientuProstego(f, x0, gtol, ftol, krok);
%[x_opt, dx, it] = metodaNajszybszegoSpadku(f, x0, gtol, ftol, krok);

[X,Y] = meshgrid(linspace(xp,xk), linspace(yp,yk));
Z = reshape(f([X(:), Y(:)]'), size(X));
figure('Name', sprintf('f(%f,%f)=%f, #it=%d', x_opt(1), x_opt(2), f(x_opt), it))
contour(X,Y,Z,100)
line(dx(1,:), dx(2,:), 'Color', 'k')  % ścieżka od x0 do x_opt

function [x_opt, dx, it] = metodaGradientuProstego(f, x0, gtol, ftol, krok)
    dx = [x0];
    it = 1;
    g = grad(f,x0);
    f0 = f(x0);
    gnorm = norm(g);

    while true
        if gnorm < gtol
            break;
        end

        f1 = f(x0-(krok*g));

        if f1 < f0
            x0 = x0 -(krok*g);
            dx(:,end+1) = x0;

            if abs((f1-f0)/(f0)) <= ftol
                break;
            end

            f0 = f1;
            g = grad(f,x0);
            gnorm = norm(g);
        else
            krok = krok/2;
        end

        it = it + 1;
    end

    x_opt = x0;
end

function [x_opt, dx, it] = metodaNajszybszegoSpadku(f, x0, gtol, ftol, krok)
    dx = [x0];
    it = 1;
    g = grad(f,x0);
    f0 = f(x0);
    gnorm = norm(g);

    alfa = 0.1;
    beta = 0.5;

    u = (-1)*g;
    gTu = dot(g,u);

    while true
        if gnorm < gtol
            break;
        end

        t = 1;

        u = (-1)*g;
        gTu = dot(g,u);

        while (f(x0 + (t*u))) > (f(x0) + (alfa*gTu*t))
            t = t*beta;
        end

        x0 = x0 + t*u;
        f1 = f(x0);
        dx(:,end+1) = x0;

        if abs((f1-f0)/(f0)) <= ftol
            break;
        end

        f0 = f1;
        g = grad(f,x0);
        gnorm = norm(g);

        it = it + 1;
    end

    x_opt = x0;
end

function g = grad(f,x)
    n = length(x);
    h = 2^(-16);
    g = zeros(n,1);

    for i = 1:n
        xi = x(i);
        x(i) = xi + h;
        fp = f(x);

        x(i) = xi - h;
        fn = f(x);

        g(i) = (fp-fn)/(2*h);
        x(i) = xi;
    end
end