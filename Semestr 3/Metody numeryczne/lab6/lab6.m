clc
close all
clear all

p = 1;

switch p
    case 1
        A = [2,2,1;1,4,1;0,1,2];
        B = [3;-1;1];
    case 2
        A = [4,1,4;2,-1,2;1,1,2];
        B = [2;-4;-1];
    case 3
        A = [2,2,1,-1;0,3,1,2;1,2,2,1;1,1,1,0];
        B = [6;-1;4;4];
    otherwise
        A = [2,1,-1;0,3,1;-2,1,4];
        B = [4;-2;-4];
end

% n = 10;
% x = randn(n,1);
% A = randn(n);
% B = A*x;

% [l,u] = lu(A);
[L,U] = doolittle(A);
% norm (l-L)
% norm(u-U)

x = rozwiazywanie(L,U,B);
norm(A*x-B)