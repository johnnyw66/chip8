# Compiler
CC = gcc
FLAGS= -g

# Frameworks directory (point to your framework directory)
FRAMEWORK_DIR = /Library
BIN_DIR=./bin
SRC_DIR=./src
# Compilation flags (for header search, pointing to SDL2 subdirectory)
CFLAGS = -F$(FRAMEWORK_DIR) -I$(FRAMEWORK_DIR)/SDL2.framework/Headers -I./include

# Linker flags (for framework linking)
LDFLAGS = -rpath $(FRAMEWORK_DIR) -framework SDL2

# Source file and output executable
SRC = ${SRC_DIR}/main.c ${SRC_DIR}/chip8memory.c  ${SRC_DIR}/chip8stack.c ${SRC_DIR}/chip8keyboard.c ${SRC_DIR}/chip8.c
OUT = $(BIN_DIR)/main

# Default target
all: $(OUT)

# Compile and link
$(OUT): $(SRC)
	$(CC) $(CFLAGS) -o $(OUT) $(SRC) $(LDFLAGS)

# Clean up
clean:
	rm -f $(OUT)

# Run the program
run: $(OUT)
	./$(OUT)





