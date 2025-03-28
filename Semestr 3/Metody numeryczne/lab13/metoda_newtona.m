function [x, n] = metoda_newtona(f, a, b, eps)
    h = 10^(-5);

    pierwszaPochodnaA = (f(a+h)-f(a-h))/(2*h);
    pierwszaPochodnaB = (f(b+h)-f(b-h))/(2*h);

    if abs(pierwszaPochodnaA) < abs(pierwszaPochodnaB)
        x = a;
    else
        x = b;
    end

    n = 1;

    while true
        pierwszaPochodna = (f(x+h)-f(x-h))/(2*h);

        if (abs(pierwszaPochodna) < eps)
            if (f(x) > f(a))
                x = a;
                break;
            else if (f(x) > f(b))
                x = b;
                break;
            else
                break;
            end
            end
        end

        drugaPochodna = (f(x+h) - 2*f(x) + f(x-h))/(h*h);

        x = x - (pierwszaPochodna/drugaPochodna);

        n = n + 1;
    end

    if (x > b)
        x = b;
    else if (x < a)
        x = a;
    end
end