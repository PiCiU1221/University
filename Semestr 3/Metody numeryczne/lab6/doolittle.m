function [L,U] = doolittle(A,B)

[m,n] = size(A);

assert(m==n)
L = eye(n);
U = zeros(n);

for i=1:n
    for j=1:n
        if i>j
            wynik1 = 0;

            for k=1:j-1
                wynik1 = wynik1 + L(i,k) * U(k,j);
            end

            L(i,j) = (A(i,j) - wynik1) / U(j,j);
        else
            wynik2 = 0;

            for k=1:i-1
                wynik2 = wynik2 + L(i,k) * U(k,j);
            end

            U(i,j) = A(i,j) - wynik2;
        end
    end
end

end

