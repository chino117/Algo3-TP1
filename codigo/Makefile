.PHONY: all clean debug

all: main.cpp
	g++ -std=c++11 -Wall -O2 -o main $^

debug: main.cpp
	g++ -std=c++11 -Wall -g -Og -o main $^

clean:
	rm -f main *.o
