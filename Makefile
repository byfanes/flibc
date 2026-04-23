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
  -Wfloat-equal -Wcast-align \
  -Wswitch-default -Wunreachable-code

CFLAGS := \
  -fno-builtin -nostdinc -Iinclude/ \
  -std=$(STDC) $(OPT) $(WARN_CFLAGS) -ffreestanding

AR      := ar
ARFLAGS := rcs

SRC_DIR   := src
TEST_DIR  := tests
BUILD_DIR := build

TARGET := libflibc.a
EXEC   := main

SRCS := $(shell find $(SRC_DIR) -name '*.c')
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

TEST_SRC  := $(shell find $(TEST_DIR) -name '*.c')
TEST_OBJS := $(TEST_SRC:$(TEST_DIR)/%.c=$(BUILD_DIR)/$(TEST_DIR)/%.o)
TEST_OUT  := $(TEST_SRC:$(TEST_DIR)/%.c=$(BUILD_DIR)/$(TEST_DIR)/%)

.PHONY: all clean tests test_run

all: $(TARGET) $(EXEC)

build_tests: $(TARGET) $(TEST_OUT)

check: build_tests
	@for t in $(TEST_OUT); do \
		echo "Running $$t"; \
		$$t || exit $$?; \
	done; \
	echo "All tests passed"

# ---- libc ----
$(TARGET): $(OBJS)
	@echo "Archiving $@"
	@$(AR) $(ARFLAGS) $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "Compiling libc $<"
	@$(CC) $(CFLAGS) -c $< -o $@

# ---- main (hosted) ----
$(EXEC): main.c $(TARGET)
	@echo "Linking executable $@"
	@$(CC) $(CFLAGS) $< -o $@ -L. -lflibc

# ---- tests (hosted) ----
$(BUILD_DIR)/$(TEST_DIR)/%.o: $(TEST_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "Compiling test $<"
	@$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/$(TEST_DIR)/%: $(BUILD_DIR)/$(TEST_DIR)/%.o $(TARGET)
	@echo "Linking test $@"
	@$(CC) $(CFLAGS) $< -o $@ -L. -lflibc

clean:
	@echo "Cleaning up..."
	@rm -rf $(BUILD_DIR) $(TARGET) $(EXEC)
