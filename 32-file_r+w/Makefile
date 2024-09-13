CC = tcc

SRC_DIR = src
SRC = *.c

BLD_DIR = bld
BLD = main

INCL = -Iinclude
CFLAGS = $(shell sdl2-config --cflags)
LIBS = $(shell sdl2-config --libs) -lSDL2_ttf
OPTS = -std=c89 -Wall -Wextra

ifeq ($(CC),gcc)
	XOPTS  =  --pedantic -g3
else
	XOPTS  =  -DSDL_DISABLE_IMMINTRIN_H -pedantic
endif
ARGS = $(SRC_DIR)/$(SRC) $(INCL) $(CFLAGS) $(LIBS) $(OPTS) $(XOPTS)

$(BLD): $(OBJS)
	$(CC) -o $(BLD_DIR)/$@ $(ARGS)
run:
ifeq  ($(CC),gcc)
	$(error Use tcc to run)
else
	$(CC) $(ARGS) -run
endif
.PHONY:
clean:
	rm $(BLD_DIR)/$(BLD)

