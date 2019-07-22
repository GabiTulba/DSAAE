.PHONY: all clean

MKFILE_PATH = $(abspath $(lastword $(MAKEFILE_LIST)))
PRJ_ROOT = $(dir $(MKFILE_PATH))

SOURCES = $(PRJ_ROOT)src/main.cpp
INCLUDE = $(PRJ_ROOT)src

OBJS = $(SOURCES:.cpp=.o)
CC = g++

COMPILER_FLAGS = -std=gnu++17 -g -Wall -Wextra -Werror -I$(INCLUDE)
LINKER_FLAGS = -lSDL2

EXE_NAME = test.elf64

all :
	$(CC) $(SOURCES) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(EXE_NAME)

clean:
	rm -rf $(EXE_NAME) $(OBJS)
