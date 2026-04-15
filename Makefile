# --- Toolchain & Flags ---
CC      := gcc
CFLAGS  := -ffreestanding -fno-builtin -nostdinc -Iinclude/ -Wall -Wextra
AR      := ar
ARFLAGS := rcs

# --- Directories ---
SRC_DIR   := src
BUILD_DIR := build

# --- Output Target ---
# It is highly recommended to output a static library (.a) instead of a .o file
TARGET := libflibc.a

# --- File Finding ---
# Find all .c files inside src/ and its subdirectories
SRCS := $(shell find $(SRC_DIR) -name '*.c')

# Map the source files to object files inside the build/ directory
# Example: src/math/abs.c -> build/math/abs.o
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# --- Rules ---
.PHONY: all clean

# Default rule
all: $(TARGET)
	@$(CC) -o main main.c -lflibc -L. $(CFLAGS)

# Rule to link all .o files into the final static library
$(TARGET): $(OBJS)
	@echo "Archiving $@"
	@$(AR) $(ARFLAGS) $@ $^

# Rule to compile .c files into .o files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@# Create the specific subdirectory inside build/ if it doesn't exist
	@mkdir -p $(dir $@)
	@echo "Compiling $<"
	@$(CC) $(CFLAGS) -c $< -o $@

# Clean up generated files
clean:
	@echo "Cleaning up..."
	@rm -rf $(BUILD_DIR) $(TARGET)
