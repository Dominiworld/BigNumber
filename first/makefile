all:	
	gcc -std=gnu99 -c -fPIC first.c -o first.o
	gcc -shared -o libfirst.so first.o
	gcc -c main.c
	gcc main.o -L. -lfirst -o RES
	


	
