all:	
	gcc -std=gnu99 -c -fPIC 1.c -o 1.o
	gcc -shared -o libfirst.so 1.o
	g++ -c -fPIC 2.cpp -o 2.o
	g++ -shared -L. -lfirst -o libsecond.so 2.o
	swig -c++ -python -o third_wrap.cpp third.i
	gcc -c -fPIC third_wrap.cpp -o third_wrap.o -I/usr/include/python2.7
	g++ -fPIC -shared third_wrap.o -L. -lsecond -lfirst -o _third.so


	
