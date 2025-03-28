function [X] = eliminacjaGaussa(A, B)

n = length(B);
A=[A B];

for i=1:n
    [~,k]=max(abs(A(i:n,i)));
    
    k = k + i - 1;

    T = A(k,:);
    A(k,:) = A(i,:);
    A(i,:) = T;
    
    for j=i+1:n
        % A(j,i) + w * A(i,j) = 0;
        % w * A(i,j) = - A(j,i)

        w = -A(j,i)/A(i,i);
        A(j,:)=A(j,:) + A(i,:) * w;
    end
end

X = zeros(size(B));

X(n)=A(n,end)/A(n,n);

for i=n-1:-1:1
    X(i)=(A(i,end)-A(i,i+1:n)*X(i+1:n))/A(i,i);
end

X

end
