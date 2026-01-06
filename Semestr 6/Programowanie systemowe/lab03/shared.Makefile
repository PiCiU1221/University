lab03_zad2: main.o libshared.so
	gcc -o lab03_zad2 main.o
	rm -f main.o lib.o

libshared.so: lib.o
	gcc -shared -o libshared.so lib.o

lib.o: lib.c
	gcc -c lib.c

main.o: main.c
	gcc -c main.c
