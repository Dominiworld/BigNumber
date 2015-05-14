all:	
	gcc -std=gnu99 -c -fPIC 1.c -o 1.o
	gcc -shared -o lib1.so 1.o
	g++ -c -fPIC 2.cpp -o 2.o
	g++ -shared -L. -l1 -o lib2.so 2.o
	g++ -c main.cpp
	g++ main.o -L. -l2 -L. -l1 -o RES
	


	
