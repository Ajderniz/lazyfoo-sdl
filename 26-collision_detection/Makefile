CC = tcc

SRC_DIR = src
SRC = *.c

BLD_DIR = bld
BLD = main

CFLAGS = $(shell sdl2-config --cflags)
LIBS = $(shell sdl2-config --libs)
OPTS = -std=c89 -Wall -Wextra -DUSE_LOG_DEBUG -DUSE_LOG_ERROR
ifeq ($(CC),gcc)
	XOPTS = --pedantic -g3
else
	XOPTS = -DSDL_DISABLE_IMMINTRIN_H
endif
ARGS = $(SRC_DIR)/$(SRC) $(INCLUDE_PATHS) $(CFLAGS) $(LIBS) $(OPTS) $(XOPTS)

all: $(OBJS)
	$(CC) -o $(BLD_DIR)/$(BLD) $(ARGS)
run:
ifeq  ($(CC),gcc)
	$(error Use tcc to run)
else
	$(CC) $(ARGS) -run
endif
.PHONY:
clean:
	rm $(BLD_DIR)/$(BLD)

