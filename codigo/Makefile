.PHONY: all clean debug

CCX = g++
FLAGS = -std=c++11 -Wall -O2
DEBUG_FLAGS = -std=c++11 -Wall -g -Og
SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)

%.o: %.cpp
	$(CCX) $(DEBUG_FLAGS) -c -o $@ $^

all: $(OBJ)
	$(CCX) $(FLAGS) -o main $^

debug: $(OBJ)
	$(CCX) $(DEBUG_FLAGS) -o main $^
clean:
	rm -f $(OBJ) main
