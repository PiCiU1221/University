function [x,f] = lab20funkcja(A,b,c,tol)

[m,n] = size(A);

for i = 1:m
    for j = m+1:n+m
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

x = ones(m+n,1);
y = ones(m,1);
z = ones(m+n,1);

sigma = 0.9;
delta = 0.02;

while 1
    rp = A * x - b;
    rd = A' * y + z - c;
    xz = dot(x,z);
    if norm(rp) < tol && norm(rd) < tol && xz < tol
        break;
    end
    tau = ((1/n) * x' * z) * delta;
    e = ones(size(x));
    dy = linsolve(A*diag(x./z) * A',-rp + A*(x - diag(tau./z) * e - diag(x./z) * rd));
    dz = -A' * dy - rd;
    dx = -diag(x./z) * dz + diag(tau./z) * e - x;
    ap = 1;
    ad = 1;

    for j = 1:length(x)
        if x(j) + ap * dx(j) < 0
            ap = -(x(j)/dx(j));
        end
    end

    for j = 1:length(x)
        if z(j) + ad * dz(j) < 0
            ad = -(z(j)/dz(j));
        end
    end

    ap = ap * sigma;
    ad = ad * sigma;

    x = x + ap * dx;
    y = y + ad * dy;
    z = z + ad * dz;
end

f = c' * x;
x = x(1:n);

end

