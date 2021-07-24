.PHONY=all, all_dbg, clean

CC=clang++
SANITIZE=-fsanitize=address -fno-omit-frame-pointer
CEXTRA:= -O2
CFLAGS= $(CEXTRA) $(SANITIZE) -std=c++20 -Wall -Wextra
CFLAGS_DBG:=-g -march=haswell -std=c++20 -Wall -Wextra
LDFLAGS=

SRCS=$(wildcard src/*.cpp)
OBJS=$(patsubst src/%.cpp, obj/%.o, $(SRCS))
OBJS_DBG=$(patsubst src/%.cpp, obj_dbg/%.o, $(SRCS))
HEADERS=-Iheader -I../Matrix/header

all: obj test
all_dbg: obj_dbg test_dbg

# build matrix objects and build program
test: test.cpp $(OBJS)
	@cd ../Matrix && make build_src
	$(CC) $(CFLAGS) $(HEADERS) $^ $(wildcard ../Matrix/obj/*.o) -o test

test_dbg: test.cpp $(OBJS_DBG)
	@cd ../Matrix && make build_src_dbg
	$(CC) $(CFLAGS_DBG) $(HEADERS) $^ $(wildcard ../Matrix/obj_dbg/*.o) -o test_dbg

$(OBJS) :  obj/%.o : src/%.cpp
	$(CC) $(CFLAGS) $(HEADERS) $< -o $@ $(LDFLAGS) -c

$(OBJS_DBG) :  obj_dbg/%.o : src/%.cpp
	$(CC) $(CFLAGS_DBG) $(HEADERS) $< -o $@ $(LDFLAGS) -c

obj:
	@mkdir -p obj

obj_dbg:
	@mkdir -p obj_dbg

clean:
	@cd ../Matrix && make clean
	rm obj/*.o
	rm obj_dbg/*.o
	rm -f test
