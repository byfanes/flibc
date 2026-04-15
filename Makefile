# --- Toolchain & Flags ---
CC      := gcc
# Added -nostdlib here just to be safe, though it's mainly for linking
CFLAGS  := -ffreestanding -fno-builtin -nostdinc -nostdlib -Iinclude/ -Wall -Wextra
AR      := ar
ARFLAGS := rcs

# --- Directories ---
SRC_DIR   := src
BUILD_DIR := build

# --- Output Targets ---
TARGET := libflibc.a
EXEC   := main

# --- File Finding ---
SRCS := $(shell find $(SRC_DIR) -name '*.c')
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# --- Rules ---
.PHONY: all clean

# Default rule builds both the library and the executable
all: $(TARGET) $(EXEC)

# Rule to build the executable (depends on main.c and libflibc.a)
$(EXEC): main.c $(TARGET)
	@echo "Linking executable $@"
	@$(CC) $(CFLAGS) $< -o $@ -L. -lflibc

# Rule to link all .o files into the final static library
$(TARGET): $(OBJS)
	@echo "Archiving $@"
	@$(AR) $(ARFLAGS) $@ $^

# Rule to compile .c files into .o files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "Compiling $<"
	@$(CC) $(CFLAGS) -c $< -o $@

# Clean up generated files
clean:
	@echo "Cleaning up..."
	@rm -rf $(BUILD_DIR) $(TARGET) $(EXEC) main.o
