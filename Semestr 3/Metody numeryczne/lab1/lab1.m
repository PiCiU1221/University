clc % czyszczenie okna komend
close all % zamkniecie wszystkich otwartych wykresow
clear all % czyszczenie wszystkich zmiennych

a = 6;
b = 5.5;
s = 'abc';

A = [1 2 3 4];
A = [1; 2; 3; 4];


B = [ -12 , -11 , -10 , -9; 8 , 7, 6, 5; 1 , 2, 3, 4];

% ZAD 1
sum(B, 2);

% ZAD 2
min(B,[],2);

% ZAD 3
% A * B  ) NIE,
% B * A  ) TAK,
% A * B' ) NIE,
% B * A' ) NIE,

% ZAD 4
B([1,3], :);

% ZAD 5
A(end+1: end+2) = [5 6];
A = [A; 7];

% ZAD 6
B = [B sum(B, 2)];

% ZAD 7
C = randi (10 , 5, 4);

for i = 1:numel(C)
    if mod(C(i),2) == 0
        C(i) = 0;
    else 
        C(i) = 100;
    end
end

C;

for i = 1:4
    for j = 1:5
        if mod(C(j,i),2) == 0
            C(j,i) = 0;
        else if mod(C(j,i),2) == 1
                C(j,i) = 100;
        end
        end
    end
end

C;

% ZAD 8
C = randi (10 , 5, 4);

L = mod(C,2) == 1;
C(L) = 100;
C(~L) = 0;

C;
