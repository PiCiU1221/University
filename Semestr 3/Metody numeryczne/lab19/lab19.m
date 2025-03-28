clc
close all
clearvars

A = [2,1;3,3;2,0];
b = [10;24;8];
c = [300;200];

[m,n] = size(A);

% A = [ A | I ]
% c = [ c|0 ]

for i = 1:m
    for j = m:n+m
        if (j == n+i)
            A(i,j) = 1;
        else
            A(i,j) = 0;
        end
    end
end

for i = n+1:m+n
    c(i,1) = 0;
end

for i = m:m+n
    wb(i-n,1) = i;
end

while true
    cb = c(wb);
    f = cb' * b;
    ww = c' - cb' * A;

    if all(ww(1,:) <= 0)
        break;
    end

    [~,kk] = max(ww);

    for i = 1:length(b)
        temp = b(i,1) / A(i,kk);
        if (temp >= 0)
            ilorazy(i,1) = b(i,1) / A(i,kk);
        else
            ilorazy(i,1) = inf;
        end
    end

    [~,wk] = min(ilorazy);
    er = A(wk,kk);

    wb(wk) = kk;
    cb(wk) = c(wk);


    b(wk) = b(wk) / er;

    for i = 1:m+n
        A(wk, i) = A(wk, i) / er;
    end

    for i = 1:m
        if (i ~= wk) 
            number = A(i,kk);
            b(i) = b(i) - (number*b(wk));
            for j = 1:m+n
                A(i,j) = A(i,j) - (number*A(wk,j));
            end
        end
    end
end

for i = 1:n
    if (A(i,1) == 1)
        x1 = b(i)
    end
end

for i = 1:n
    if (A(i,2) == 1)
        x2 = b(i)
    end
end