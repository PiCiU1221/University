function Y = wart(a,X,x)

n = length(a);

for m=1:length(X)
    suma=0;
    for i=1:n
        mnozenie = 0;
        obliczenia = 1;

        for j=1:n
            if (j == i) 
                continue;
            end
    
            obliczenia = obliczenia * (X(m) - x(j));
        end

        mnozenie = a(i)*obliczenia;

        suma = suma + mnozenie;
    end
    
    Y(m) = suma;
end

end

