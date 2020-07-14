#
#  To sa opcje dla kompilacji
#
CXXFLAGS=-g -Iinc -Wall -pedantic -std=c++17


grafy: main.o graf.o matrix.o list.o

	g++  -g -Wall -pedantic -std=c++17 -o grafy main.o graf.o matrix.o list.o\

graf.o:  vector.hh graf.hh graf.cpp
	g++ -c ${CXXFLAGS} -o graf.o graf.cpp

matrix.o:  graf.hh matrix.hh matrix.cpp
	g++ -c ${CXXFLAGS} -o matrix.o matrix.cpp

list.o:  graf.hh list.hh list.cpp
	g++ -c ${CXXFLAGS} -o list.o list.cpp

main.o: main.cpp matrix.hh list.hh
	g++ -c ${CXXFLAGS} -o main.o main.cpp

clean:
	rm -f *.o  *.txt grafy 
