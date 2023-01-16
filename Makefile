CC = g++

all: market mm

market: market.o
	g++ -o market market.o

market.o: utils/utils.h utils/marketmaker.h market.cpp
	g++ -c utils/utils.h utils/marketmaker.h market.cpp

mm: marketmaker.o
	g++ -o mm marketmaker.o

marketmaker.o: utils/utils.h utils/options.h utils/marketmaker.h marketmaker.cpp
	g++ -c utils/utils.h utils/options.h utils/marketmaker.h marketmaker.cpp

clean:
	rm *.o market mm
