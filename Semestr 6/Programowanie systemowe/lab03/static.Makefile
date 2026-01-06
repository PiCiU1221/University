lab03_zad1: main.o libstatic.a
	gcc -o lab03_zad1 main.o -L. -lstatic
	rm -f main.o lib.o

libstatic.a: lib.o
	ar rcs libstatic.a lib.o

main.o: main.c
	gcc -c main.c

lib.o: lib.c
	gcc -c lib.c
