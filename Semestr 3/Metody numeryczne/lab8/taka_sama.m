function [wynik] = taka_sama(X,Y)

    for i=1:length(X)
        if (X(i) > 13)
            target = i;
            break;
        end
    end

    for i=target:length(X)
        if (Y(i) < Y(target))
            wynik = X(i);
            break;
        end
    end
end