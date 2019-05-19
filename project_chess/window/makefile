all: test

test: w1.o test1.o pole.o
	g++  test1.o w1.o pole.o `wx-config --libs` -o Easy_Debut -L./ -limage

w1.o: w1.cpp
	g++ -c w1.cpp `wx-config --cflags` -O2 

test1.o: test1.cpp
	g++ -c test1.cpp `wx-config --cflags` -O2

te.o: pole.cpp
	g++ -c pole.cpp `wx-config --cflags` -O2

clean: 
	rm -rf test  *.o

