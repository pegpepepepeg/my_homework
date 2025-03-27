all:
	g++ -O3 -I. -o tests.o LongNumber.cpp tests.cpp

test:
	g++ -O3 -I. -o tests.o LongNumber.cpp tests.cpp
	./tests.o
