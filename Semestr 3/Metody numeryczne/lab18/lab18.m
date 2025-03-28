clc
close all
clearvars

A = [3,2,1;5,4,3;1,1,0;-1,0,0;0,-1,0;0,0,-1];
b = [120;300;50;0;0;0];
c = [12;8;10];

eps = 10^(-13);

[m,n] = size(A);
x_feas = [];

wektor = 1:size(b);

C = nchoosek(wektor, n);

for i = C'
    Ai = A(i,:);
    bi = b(i);

    if det(Ai) == 0
        continue;
    end

    x = linsolve(Ai, bi);

    if all(A*x - b <= eps)
        x_feas(:,size(x_feas,2) + 1) = x;
    end
end

T = convhull(x_feas(1,:), x_feas(2, :), x_feas(3, :));
trisurf(T, x_feas(1,:), x_feas(2, :), x_feas(3, :));
hold on

[~,k] = max(c' * x_feas);

x = x_feas(1, k);
y = x_feas(2, k);
z = x_feas(3, k);

plot3(x,y,z, 'r*');