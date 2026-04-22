CC     := clang
STDC   := c99
OPT    := -O3 -g3

WARN_CFLAGS := \
  -Wall -Wextra -Wpedantic -pedantic \
  -Wconversion -Wsign-conversion \
  -Wformat -Wformat-overflow -Wformat-truncation \
  -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations \
  -Wshadow -Wpointer-arith \
  -Wwrite-strings -Wundef \
  -Wbad-function-cast \
  -Wnull-dereference \
  -Wimplicit-fallthrough \
  -fstack-protector-strong \
  -fno-strict-aliasing -fwrapv -Wfloat-equal -Wcast-align -Wstrict-overflow=5 \
  -Wswitch-default -Wconversion -Wunreachable-code

MANDA_CFLAGS := -ffreestanding -fno-builtin -nostdinc -nostdlib -Iinclude/
CFLAGS  := $(MANDA_CFLAGS) -std=$(STDC) $(WARN_CFLAGS) $(OPT)
AR      := ar
ARFLAGS := rcs

SRC_DIR   := src
BUILD_DIR := build

TARGET := libflibc.a
EXEC   := main

SRCS := $(shell find $(SRC_DIR) -name '*.c')
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

.PHONY: all clean

all: $(TARGET) $(EXEC)

$(EXEC): main.c $(TARGET)
	@echo "Linking executable $@"
	@$(CC) $(CFLAGS) $< -o $@ -L. -lflibc

$(TARGET): $(OBJS)
	@echo "Archiving $@"
	@$(AR) $(ARFLAGS) $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "Compiling $<"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Cleaning up..."
	@rm -rf $(BUILD_DIR) $(TARGET) $(EXEC) main.o
