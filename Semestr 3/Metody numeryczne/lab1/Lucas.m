function [L] = Lucas(n)
    if n == 0
        L = 2;
    else 
        L = [2,1];
        for i = 3:n
            L(i) = L(i-1) + L(i-2);
        end
    end
end