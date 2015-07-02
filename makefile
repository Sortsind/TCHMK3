all:
	
	swig -c++ -python long_class.i
	g++ -c -w -std=c++11 long_class.cpp
	g++ -c -w -std=c++11 long_numeric.cpp
	g++ -c -w -std=c++11 long_class_wrap.cxx -I/Library/Frameworks/Python.framework/Versions/2.7/include/python2.7
	g++ -lpython -dynamiclib long_class.o long_numeric.o long_class_wrap.o -o _long_class.so
