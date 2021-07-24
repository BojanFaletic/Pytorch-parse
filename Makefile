# This is top level Makefile, it build loader, matrix, layers
# output from this is working model

.PHONY:build, debug, clean, help, all
SHELL := bash
.SHELLFLAGS := -eu -o pipefail -c


# Copiler flags
CXX=clang++
LD=clang++

SANITIZE= -Wall -fsanitize=address -fno-omit-frame-pointer

CXXFLAGS=-std=c++20 -Wall -Wextra -O2 -Wpedantic -c
CXXFLAGS_DBG=-std=c++20 $(SANITIZE) -c
LDFLAGS= -lzip  $(SANITIZE)

# Name of project (top file)
PROJECT_NAME = model


# directories in project
SRC_MATRIX_DIR = Matrix/src/
SRC_LOADER_DIR = loader/src/
SRC_LAYER_DIR =  layers/src/

# find all object name from different directories
MATRIX_SRCS = $(wildcard $(SRC_MATRIX_DIR)*.cpp)
LAYER_SRCS = $(wildcard $(SRC_LAYER_DIR)*.cpp)
LOADER_SRCS = $(wildcard $(SRC_LOADER_DIR)*.cpp)

MATRIX_OBJS = $(patsubst %.cpp, %.o, $(addprefix obj/, $(notdir $(MATRIX_SRCS))))
LAYER_OBJS = $(patsubst %.cpp, %.o, $(addprefix obj/, $(notdir $(LAYER_SRCS))))
LOADER_OBJS = $(patsubst %.cpp, %.o, $(addprefix obj/, $(notdir $(LOADER_SRCS))))

MATRIX_OBJS_DBG = $(patsubst %.cpp, %.o, $(addprefix obj_dbg/, $(notdir $(MATRIX_SRCS))))
LAYER_OBJS_DBG = $(patsubst %.cpp, %.o, $(addprefix obj_dbg/, $(notdir $(LAYER_SRCS))))
LOADER_OBJS_DBG = $(patsubst %.cpp, %.o, $(addprefix obj_dbg/, $(notdir $(LOADER_SRCS))))

# list of all possible object required for project
OBJ_ALL = obj/$(PROJECT_NAME).o $(MATRIX_OBJS) $(LAYER_OBJS) $(LOADER_OBJS)
OBJ_ALL_DBG = obj_dbg/$(PROJECT_NAME).o $(MATRIX_OBJS_DBG) $(LAYER_OBJS_DBG) $(LOADER_OBJS_DBG)


# build all
all: build debug

# top level wrapper
build:  obj $(PROJECT_NAME)
debug: obj_dbg $(PROJECT_NAME)_dgb

help:
	@echo 'all' build evrything
	@echo 'build' build project
	@echo 'build_debug' build project for debugging


# build project
$(PROJECT_NAME) : $(OBJ_ALL)
	$(LD) $^ $(LDFLAGS) -o $(PROJECT_NAME)

# build debug file
$(PROJECT_NAME)_dgb : $(OBJ_ALL_DBG)
	$(LD) $^ $(LDFLAGS) -o $(PROJECT_NAME)_dgb


# build all objects
obj/$(PROJECT_NAME).o : obj/%.o : %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

$(MATRIX_OBJS): obj/%.o : $(SRC_MATRIX_DIR)%.cpp
	$(CXX) -IMatrix/header $(CXXFLAGS) $< -o $@

$(LAYER_OBJS): obj/%.o : $(SRC_LAYER_DIR)%.cpp
	$(CXX) -IMatrix/header -Ilayers/header $(CXXFLAGS) $< -o $@

$(LOADER_OBJS): obj/%.o : $(SRC_LOADER_DIR)%.cpp
	$(CXX) -Iloader/header $(CXXFLAGS) $< -o $@

# build all objcets used for debugging
obj_dbg/$(PROJECT_NAME).o : obj_dbg/%.o : %.cpp
	$(CXX) $(CXXFLAGS_DBG) $< -o $@

$(MATRIX_OBJS_DBG): obj_dbg/%.o : $(SRC_MATRIX_DIR)%.cpp
	$(CXX) -IMatrix/header $(CXXFLAGS_DBG) $< -o $@

$(LAYER_OBJS_DBG): obj_dbg/%.o : $(SRC_LAYER_DIR)%.cpp
	$(CXX) -IMatrix/header -Ilayers/header $(CXXFLAGS_DBG) $< -o $@

$(LOADER_OBJS_DBG): obj_dbg/%.o : $(SRC_LOADER_DIR)%.cpp
	$(CXX) -Iloader/header $(CXXFLAGS_DBG) $< -o $@


# build obj dir
obj:
	mkdir -p $@

obj_dbg:
	mkdir -p $@

# clean files
clean:
	rm -f $(PROJECT_NAME)
	rm -f $(PROJECT_NAME)_dgb
	rm -f obj/*.o
	rm -f obj_dbg/*.o
