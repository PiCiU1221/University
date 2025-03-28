function [n] = Mirror(n)
    s = num2str(n);
    for i = 1:floor(length(s)/2)
        temp = s(i);
        s(i) = s(end-i+1);
        s(end-i+1) = temp;
    end
    n = str2num(s);
end