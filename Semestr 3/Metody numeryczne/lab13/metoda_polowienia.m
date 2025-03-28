function [x, n] = metoda_polowienia(f, a, b, eps)
    xM = (a+b)/2;

    wartoscFunkcjiA = f(a);
    wartoscFunkcjiXM = f(xM);

    n = 1;

    while true
        L = b-a;

        xL = a+0.25*L;
        xR = b-0.25*L;
        
        wartoscFunkcjiXL = f(xL);
        wartoscFunkcjiXR = f(xR);
    
        if wartoscFunkcjiA < wartoscFunkcjiXL || wartoscFunkcjiXL < wartoscFunkcjiXM
            b = xM;
            xM = xL;
            
            wartoscFunkcjiXM = wartoscFunkcjiXL;
        else if wartoscFunkcjiXM < wartoscFunkcjiXR
            a = xL;
            b = xR;

            wartoscFunkcjiA = wartoscFunkcjiXL;
        else 
            a = xM;
            xM = xR;

            wartoscFunkcjiXM = wartoscFunkcjiXR;
        end

        if (b - a) < eps
            x = (a+b)/2;
            break;
        end

        n = n + 1;

    end
   
end
