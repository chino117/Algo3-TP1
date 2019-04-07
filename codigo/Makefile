.PHONY: all clean debug

src = $(wildcard src/*.cpp)
obj = $(src:.cpp=.o)
CCX = g++
FLAGS = -std=c++11 -Wall -O2
DEBUG_FLAGS = -std=c++11 -Wall -g -Og

all: $(obj)
	$(CCX) $(FLAGS) -o main $^
debug: $(obj)
	$(CCX) $(DEBUG_FLAGS) -o main $^
clean:
	rm -f $(obj) main
