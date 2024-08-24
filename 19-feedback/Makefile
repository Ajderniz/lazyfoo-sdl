CC = gcc

SRC_DIR = src
SRC = *.c

BLD_DIR = bld
BLD = main

CFLAGS = $(shell sdl2-config --cflags)
LIBS = $(shell sdl2-config --libs) -lSDL2_image -lm
OPTS = -g3 -std=c89 -Wall -Wextra --pedantic

all: $(OBJS)
	$(CC) -o $(BLD_DIR)/$(BLD) $(SRC_DIR)/$(SRC) $(INCLUDE_PATHS) $(CFLAGS) $(LIBS) $(OPTS)
.PHONY:
clean:
	rm $(BLD_DIR)/$(BLD)
