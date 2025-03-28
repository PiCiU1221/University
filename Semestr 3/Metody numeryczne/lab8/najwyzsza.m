function [godzina] = najwyzsza(X,Y)

najwyzsza_temperatura = Y(1);
godzina = X(1);

for i=2:length(X)
    if (Y(i) > najwyzsza_temperatura)
        najwyzsza_temperatura = Y(i);
        godzina = X(i);
    end
end

end

