# Makefile for Hash Table Project

# Compiler and flags
CC = gcc
CFLAGS = -Iinclude -Wall -std=c11

# Directories
SRC_DIR = src
OBJ_DIR = bin

# Target executable name
TARGET = $(OBJ_DIR)/hash_table

# Source files
SOURCES = $(wildcard $(SRC_DIR)/*.c)

# Object files
OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SOURCES))

all: $(TARGET)

# Linking the executable
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

# Compiling source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET)
