ALL = blackjack-graphs
SRC = $(wildcard *.cpp)
OBJ = $(patsubst %.cpp, %.o, $(wildcard *.cpp))

CC = g++

CPPFLAGS = -g -Wall -std=c++14 -O3

all: $(ALL)

$(ALL): $(OBJ)
	$(CC) $(CPPFLAGS) -c $(SRC)
	$(CC) $(CPPFLAGS) $(OBJ) -o $@ 

clean:
	rm $(ALL) *.o