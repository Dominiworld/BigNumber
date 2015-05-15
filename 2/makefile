all:	
	g++ -c -fPIC 2.cpp -o 2.o -I../1
	g++ -shared -L../1 -lfirst -o libsecond.so 2.o
	g++ -c main.cpp -I../1 
	g++ main.o -L. -lsecond -L../1 -I../1 -lfirst -o RES
