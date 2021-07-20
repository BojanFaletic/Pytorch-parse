.PHONY=all,clean

CC=clang++
SANITIZE=-fsanitize=address -fno-omit-frame-pointer
CEXTRA:= -O2
CFLAGS= $(CEXTRA) $(SANITIZE) -std=c++20 -Wall -Wextra
LDFLAGS=


SRCS=$(wildcard src/*.cpp) $(wildcard ../Matrix/src/*.cpp)
HEADERS=-Iheader -I../Matrix/header

all: test.cpp $(SRCS)
	$(CC) $(CFLAGS) $(HEADERS) $^ -o test $(LDFLAGS)

clean:
	rm -f test