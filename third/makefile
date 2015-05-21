all:	
	swig -c++ -python -o third_wrap.cpp third.i
	gcc -c -fPIC third_wrap.cpp -o third_wrap.o -I/usr/include/python2.7 -I../first -I ../second
	g++ -fPIC -shared third_wrap.o -I../first -I../second -L../first -L../second -lsecond -lfirst -o _third.so


	
