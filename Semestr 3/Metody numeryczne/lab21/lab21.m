clc
close all
clearvars

x = [0 0 0
     0 1 0.1
     0 2 0.4
     0 3 0.9
     0 4 1.6
     0 5 2.5
     0 6 3.6
     2 0 0.4
     2 1 0.1
     2 2 0
     2 3 0.1
     2 4 0.4
     2 5 0.9
     2 6 1.6
     4 0 1.6
     4 1 0.9
     4 2 0.4
     4 3 0.1
     4 4 0
     4 5 0.1
     4 6 0.4
     6 0 3.6
     6 1 2.5
     6 2 1.6
     6 3 0.9
     6 4 0.4
     6 5 0.1
     6 6 0]';

[x1,x2] = meshgrid(linspace(0,6));
n = size(x,2);
z1 = x1(:)';
z2 = x2(:)';

% 1.
X = [ones(1,n);x(1,:);x(2,:)];
A = x(3,:)*X' / (X * X');

blad = mean((A*X - x(3,:)).^2);

X = [ones(1,length(z1));z1;z2];
x3 = reshape(A*X,size(x1));

figure
mesh(x1,x2,x3)
hold on
plot3(x(1,:),x(2,:),x(3,:),'*')
title(sprintf('y=x_1 + x_t, mse = %e', blad))

% 2.
X = [ones(1,n);x(1,:).*x(2,:)];
A = x(3,:)*X' / (X * X');

blad = mean((A*X - x(3,:)).^2);

X = [ones(1,length(z1));z1.*z2];
x3 = reshape(A*X,size(x1));

figure
mesh(x1,x2,x3)
hold on
plot3(x(1,:),x(2,:),x(3,:),'*')
title(sprintf('y=x_1 + x_t, mse = %e', blad))

% 3.
X = [ones(1,n);x(1,:);x(2,:);x(1,:).*x(2,:)];
A = x(3,:)*X' / (X * X');

blad = mean((A*X - x(3,:)).^2);

X = [ones(1,length(z1));z1;z2;z1.*z2];
x3 = reshape(A*X,size(x1));

figure
mesh(x1,x2,x3)
hold on
plot3(x(1,:),x(2,:),x(3,:),'*')
title(sprintf('y=x_1 + x_t, mse = %e', blad))

% 4.
X = [ones(1,n);x(1,:);x(2,:);x(1,:).*x(2,:);x(1,:).^2;x(2,:).^2];
A = x(3,:)*X' / (X * X');

blad = mean((A*X - x(3,:)).^2);

X = [ones(1,length(z1));z1;z2;z1.*z2;z1.^2;z2.^2];
x3 = reshape(A*X,size(x1));

figure
mesh(x1,x2,x3)
hold on
plot3(x(1,:),x(2,:),x(3,:),'*')
title(sprintf('y=x_1 + x_t, mse = %e', blad))

% 5.
X = [ones(1,n);x(1,:).^4;x(2,:).^4;x(1,:).*x(2,:)];
A = x(3,:)*X' / (X * X');

blad = mean((A*X - x(3,:)).^2);

X = [ones(1,length(z1));z1.^4;z2.^4;z1.*z2];
x3 = reshape(A*X,size(x1));

figure
mesh(x1,x2,x3)
hold on
plot3(x(1,:),x(2,:),x(3,:),'*')
title(sprintf('y=x_1 + x_t, mse = %e', blad))