function [x, n] = bisekcja(f, a, b, tol, ftol)
    
    assert(f(a)*f(b)<0, 'Brak miejsca zerowego')

    n = 0;

    while(true)
        if (n > 0)
            poprzedniX = x;
        end

        x = (a+b) / 2;

        if (abs(f(x)) <= ftol)
            return;
        end
        
        if (n > 0)
            if (abs(x - poprzedniX) <= tol)
                return;
            end
        end

        if (f(a) * f(x) < 0)
            b = x;
        else
            a = x;
        end

        n = n+1;
    end
    
end

