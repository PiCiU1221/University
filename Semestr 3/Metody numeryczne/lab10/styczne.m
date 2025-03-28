function [x, n] = styczne(f, a, b, tol, ftol)
    assert(f(a)*f(b)<0, 'Brak miejsca zerowego')

    h = 2^(-16);
    
    drugaPochodna = (f(a+h) - 2*f(a) + f(a-h))/(h^2);

    if (f(a) * drugaPochodna > 0)
        x = a;
    else 
        x = b;
    end

    n = 0;

    while (true)
        poprzedniX = x;

        pochodna = (f(poprzedniX+h) - f(poprzedniX-h))/(2*h);

        x = poprzedniX - (f(poprzedniX)/pochodna);

        if (abs(f(x)) <= ftol)
            break;
        end

        if (abs(x - poprzedniX) <= tol)
            break;
        end

        n = n + 1;
    end
end