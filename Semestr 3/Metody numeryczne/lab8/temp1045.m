function [wynik] = temp1045(X,Y)

    for i=1:length(X)
        if (X(i) > 10.75)
            wynik = Y(i);
            break;
        end
    end

end

