all:	
	gcc -std=gnu99 -c -fPIC 1.c -o 1.o
	gcc -shared -o libfirst.so 1.o
	gcc -c main.c
	gcc main.o -L. -lfirst -o RES
	


	
