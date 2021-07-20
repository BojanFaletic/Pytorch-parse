.PHONY=all,clean

CC=clang++
SANITIZE=-fsanitize=address -fno-omit-frame-pointer
CEXTRA:= -O2
CFLAGS= $(CEXTRA) $(SANITIZE) -std=c++20 -Wall -Wextra
LDFLAGS=-lzip

SRCS=$(wildcard src/*.cpp)

all: test.cpp $(SRCS)
	$(CC) $(CFLAGS) -Iheader $^ -o test $(LDFLAGS)

clean:
	rm -f test