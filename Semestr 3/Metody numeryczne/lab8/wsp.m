function a = wsp(x,y)

n = length(x);

a = zeros(1,n);

    for i=1:n
        mianownik = 1;

        for j=1:n
            if (j == i)
                continue;
            end

            mianownik = mianownik * (x(i)- x(j));
        end

        a(i) = y(i) / mianownik;
    end
end

