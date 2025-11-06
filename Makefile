CC=gcc
CFLAGS=-g -Wall -std=c11
DEPS = types.h
OBJ = mkdirSplitpath.o 

.DEFAULT_GOAL := main

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: main.c $(OBJ) otherCommandsDifferentVersions/otherCommands_mac_arm64.o
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f mkdirSplitpath.o main
