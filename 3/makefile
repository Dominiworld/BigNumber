all:	
	swig -c++ -python -o third_wrap.cpp third.i
	gcc -c -fPIC third_wrap.cpp -o third_wrap.o -I/usr/include/python2.7 -I../1 -I ../2
	g++ -fPIC -shared third_wrap.o -I../1 -I../2 -L../1 -L../2 -lsecond -lfirst -o _third.so


	
