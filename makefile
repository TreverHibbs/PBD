# TODO learn how this make file works
# Compiler and flags
CC = clang
CFLAGS = -Wall -std=c99 -O2

# Raylib flags via pkg-config
RAYLIB_FLAGS = $(shell pkg-config --cflags --libs raylib)

# Source and output
SRC = main.c
OUTDIR = ./build
OUT = $(OUTDIR)/game

# Build target
all:
	mkdir -p $(OUTDIR)
	$(CC) $(CFLAGS) $(SRC) -o $(OUT) $(RAYLIB_FLAGS)

# Clean target
clean:
	rm -f $(OUTDIR)
