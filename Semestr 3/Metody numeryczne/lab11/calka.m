function S = calka(f,a,b,h)

    S = 0;

    for x=a:h:b-h
        if f(x) <= f(x+h)
            poleTrapezu = (f(x) * h) + ((f(x+h)-f(x))*h/2);
        else
            poleTrapezu = (f(x+h) * h) + ((f(x)-f(x+h))*h/2);
        end

        S = S + poleTrapezu;
        
        patch([x,x+h,x+h,x],[0,0,f(x+h),f(x)],'y')
    end

    x=x+h;

    if b-x > 0
        if f(x) <= f(b)
            poleTrapezu = (f(x) * (b-x)) + ((f(b)-f(x))*(b-x)/2);
        else
            poleTrapezu = (f(b) * (b-x)) + ((f(x)-f(b))*(b-x)/2);
        end

        S = S + poleTrapezu;

        patch([x,b,b,x],[0,0,f(b),f(x)],'y')
    end
end

