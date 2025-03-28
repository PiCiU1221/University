% function [x, n] = falsi(f, a, b, tol, ftol)
%     assert(f(a)*f(b)<0, 'Brak miejsca zerowego')
% 
%     drugaPochodna = (f(a+tol) - 2*f(a) + f(a-tol))/tol^2;
% 
%     if (f(a) * drugaPochodna > 0)
%         xs = a;
%         x = b;
%     else 
%         xs = b;
%         x = a;
%     end
% 
%     n = 0;
% 
%     while (true)
%         poprzedniX = x;
% 
%         x = xs - (f(xs)/(f(x)-f(xs))) * (x - xs);
% 
%         if (abs(f(x)) <= ftol)
%             break;
%         end
% 
%         if (n > 0)
%             if (abs(x - poprzedniX) <= tol)
%                 break;
%             end
%         end
% 
%         n = n + 1;
%     end
% end

function [x, n] = falsi(f, a, b, tol, ftol)
    assert(f(a)*f(b)<0, 'Brak miejsca zerowego')

    n = 0;

    while (true)
        if (n > 0)
            poprzedniX = x;
        end

        x = a - ((f(a)*(b-a))/(f(b)-f(a)));

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

        n = n + 1;
    end
end