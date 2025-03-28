function [] = lab3zad1()
    clc
    n = 4;
    A = tril(rand(n));

    disp(A)

    norm(inv(A)-zad5a(A))

    % A=randn(2^n,2^n);
    % B=randn(2^n,2^n);
    % norm(A*B-zad3(A,B))

    %disp(zad1a(n))
    %disp(zad1b(n))
    %disp(zad1c(n))
end

% function A = zad1a(n)
%     A = zeros(n);
%     A(1,:) = 1:n;
% 
%     for i = 2:n
%         A(i,:) = [A(i-1,i:n) A(i-1,i-1:)]
%     end
% end

function A = zad1c(n)
    A = zeros(n);

    for i = 1:n
        for j = 1:n
            A(i,j) = mod(j-i,n) + 1;
        end
    end
end

% function C = zad3(A,B)
%     if all(size(A)==[2,2])
%         q1 = (A(1,1) + A(2,2)) * (B(1,1)+B(2,2));
%         q2 = (A(2,1) + A(2,2)) * B(1,1);
%         q3 = A(1,1) * (B(1,2)-B(2,2));
%         q4 = A(2,2) * (B(2,1)-B(1,1));
%         q5 = (A(1,1) + A(1,2)) * B(2,2);
%         q6 = (A(2,1) + A(1,1)) * (B(1,1)+B(1,2));
%         q7 = (A(1,2) - A(2,2)) * (B(2,1)+B(2,2));
%         C=[q1+q4-q5+q7, q2+q4; q3+q5, q1+q3-q2+q6];
%     else 
%         C=[zad3(A(1:end/2,1:end/2),B(1:end/2,1:end/2)) + zad3(A(1:end/2,end/2+1:end),B(end/2+1:end,1:end/2)),
%         zad3(A(1:end/2,1:end/2),B(1:end/2,end/2+1:end)) + zad3(A(1:end/2,end/2+1:end),B(end/2+1:end,end/2+1:end));
%         zad3(A(end/2+1:end,1:end/2),B(1:end/2,1:end/2)) + zad3(A(end/2+1:end,end/2+1:end),B(end/2+1:end,end/1:end/2)),
%         zad3(A(end/2+1:end,1:end/2),B(1:end/2,end/2+1:end)) + zad3(A(end/2+1:end,end/2+1:end),B(end/2+1:end,end/2+1:end))];
%     end
% end

function iL = zad5a(L)
    n = size(L,1);
    iL = zeros(n);

    for j = 1:n
        for i = j:n
            if i == j
                iL(i,j) = 1/L(i,j);
            else
                s = 0;
                for k = j:i-1
                    s = s + L(i,k)*iL(k,j); 
                end
                iL(i,j) = -1/L(i,i) * s;
            end
        end
    end
end