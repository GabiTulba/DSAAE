.PHONY: all build tests  clean

MKFILE_PATH = $(abspath $(lastword $(MAKEFILE_LIST)))
PRJ_ROOT = $(dir $(MKFILE_PATH))

SOURCES = $(PRJ_ROOT)src/main.cpp
INCLUDE = $(PRJ_ROOT)src

TEST_SOURCES = $(PRJ_ROOT)testing/main.cpp \
			   $(PRJ_ROOT)testing/default_test.cpp

OBJS = $(SOURCES:.cpp=.o)
CC = g++

COMPILER_FLAGS = -std=gnu++17 -g -Wall -Wextra -Werror -I$(INCLUDE)
LINKER_FLAGS = -lSDL2

EXE_NAME = change_me.elf64
TEST_EXE_NAME = test.elf64

all: build tests

# TODO: this should output a library
build:
	$(CC) $(SOURCES) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(EXE_NAME)

# TODO: this should use the library
tests:
	$(CC) $(TEST_SOURCES) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(TEST_EXE_NAME)
	./$(TEST_EXE_NAME)

clean:
	rm -rf $(EXE_NAME) $(TEST_EXE_NAME) $(OBJS)
