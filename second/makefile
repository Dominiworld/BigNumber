all:	
	g++ -c -fPIC second.cpp -o second.o -I../second
	g++ -shared -L../first -lfirst -o libsecond.so second.o
	g++ -c main.cpp -I../first 
	g++ main.o -L. -lsecond -L../first -I../first -lfirst -o RES
