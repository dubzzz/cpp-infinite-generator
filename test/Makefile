CFLAGS=-std=c++1y -Wall -I. -I/usr/local/include
LDFLAGS=-L/usr/local/lib -lgtest -pthread

test: infinite.out
	chmod u+x *.out
	./infinite.out

infinite.out: infinite.cpp ../src/infinite.hpp
	g++ -o infinite.out infinite.cpp $(CFLAGS) $(LDFLAGS)

