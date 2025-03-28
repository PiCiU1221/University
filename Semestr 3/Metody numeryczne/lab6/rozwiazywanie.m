function X = rozwiazywanie(L,U,B)

% L * y = B

[n,~] = size(L);

Y = zeros(n,1);
X = zeros(n,1);

for i=1:n
    wynik1 = 0;

    for j=1:i-1
       wynik1 = wynik1 + L(i,j) * Y(j); 
    end

    Y(i) = B(i) - wynik1;
end

for i=n:-1:1
    wynik2 = 0;

    for j=i+1:n
        wynik2 = wynik2 + U(i,j)*X(j);
    end

    X(i) = 1/U(i,i) * (Y(i) - wynik2);
end

X

end