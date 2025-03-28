function [x, n] = sieczne(f, a, b, tol, ftol)
    assert(f(a)*f(b)<0, 'Brak miejsca zerowego')
    
    h = 2^(-16);
    
    drugaPochodna = (f(a+h) - 2*f(a) + f(a-h))/(h^2);

    if (f(a) * drugaPochodna > 0)
        x = a;
        x1 = b;
    else 
        x = b;
        x1 = a;
    end

    n = 0;

    while (true)
        poprzedniX = x;

        drugaCzesc = (x1-poprzedniX)/(f(x1)-f(poprzedniX));

        x = x1 - (f(x1) * drugaCzesc);

        x1 = poprzedniX;

        if (abs(f(x)) <= ftol)
            break;
        end

        if (abs(x - poprzedniX) <= tol)
            break;
        end

        n = n + 1;
    end
end