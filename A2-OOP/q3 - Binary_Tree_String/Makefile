a3q3: tstring.o a3q3.o tnode.o tstring.h
	g++ -std=c++14 tstring.o a3q3.o tnode.o -o a3q3

tstring.o: tstring.cc tstring.h
	g++ -std=c++14 -c tstring.cc

tnode.o: tnode.cc tstring.h
	g++ -std=c++14 -c tnode.cc	

a3q3.o: a3q3.cc tstring.h
	g++ -std=c++14 -c a3q3.cc