CC := gcc
AR := ar
ARFLAGS := rcs

OPT := -O0 -g3

WARN_CFLAGS := \
  -Wall -Wextra -Wpedantic \
  -Wconversion -Wsign-conversion \
  -Wformat -Wformat-overflow -Wformat-truncation \
  -Wstrict-prototypes -Wmissing-prototypes \
  -Wshadow -Wpointer-arith \
  -Wwrite-strings -Wundef \
  -Wfloat-equal -Wcast-align -Wno-int-conversion \
  -Wswitch-default -std=c89 -ansi -pedantic -Werror

# FREESTANDING (lib + main)
FREESTANDING_CFLAGS := \
  -ffreestanding -fno-builtin -nostdinc -fPIC \
  -Iinclude $(OPT) $(WARN_CFLAGS)

# HOSTED (tests only)
HOST_CFLAGS := \
  -Iinclude $(OPT) $(FREESTANDING_CFLAGS)

SRC_DIR := src
TEST_DIR := tests
BUILD_DIR := build

TARGET_STATIC := libflibc.a
TARGET_SHARED := libflibc.so
EXEC := main

# 1. Isolate start.c from the rest of the library sources
# (Change this path if start.c is inside a subfolder, e.g., src/runtime/start.c)
START_SRC := $(SRC_DIR)/start.c
START_OBJ := $(BUILD_DIR)/start.o

# 2. Filter out start.c so it DOES NOT go into the .a or .so libraries
SRCS := $(shell find $(SRC_DIR) -name '*.c')
LIB_SRCS := $(filter-out $(START_SRC), $(SRCS))
LIB_OBJS := $(LIB_SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

TEST_SRC := $(shell find $(TEST_DIR) -name '*.c')
TEST_OBJS := $(TEST_SRC:$(TEST_DIR)/%.c=$(BUILD_DIR)/$(TEST_DIR)/%.o)
TEST_OUT := $(TEST_SRC:$(TEST_DIR)/%.c=$(BUILD_DIR)/$(TEST_DIR)/%)

.PHONY: all clean tests check

all: $(TARGET_STATIC) $(TARGET_SHARED) $(EXEC)

tests: $(TEST_OUT)

check: tests
	@echo "--- Running Tests ---"
	@for test in $(TEST_OUT); do \
		echo "Running $$test..."; \
		./$$test || exit 1; \
	done
	@echo "--- All tests passed! ---"

# STATIC LIBRARY
$(TARGET_STATIC): $(LIB_OBJS)
	@echo "Archiving $@"
	@$(AR) $(ARFLAGS) $@ $^

# SHARED LIBRARY
$(TARGET_SHARED): $(LIB_OBJS)
	@echo "Linking shared library $@"
	@$(CC) -shared -nostdlib -o $@ $^

# Rule for building the library objects
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "Compiling lib $<"
	@$(CC) $(FREESTANDING_CFLAGS) -c $< -o $@

# 3. Rule for explicitly building your runtime object
$(START_OBJ): $(START_SRC)
	@mkdir -p $(dir $@)
	@echo "Compiling runtime start object $<"
	@$(CC) $(FREESTANDING_CFLAGS) -c $< -o $@

# MAIN
# 4. We explicitly link $(START_OBJ) here so _start is injected into the executable
$(EXEC): main.c $(START_OBJ) $(TARGET_SHARED)
	@echo "Linking freestanding executable $@"
	@$(CC) \
	    $(FREESTANDING_CFLAGS) \
	    -nostdlib -nostartfiles \
	    -Wl,-e,_start \
	    $(START_OBJ) main.c -L. -lflibc -Wl,-rpath=. -o $@

# TESTS (HOSTED)
$(BUILD_DIR)/$(TEST_DIR)/%.o: $(TEST_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "Compiling test $<"
	@$(CC) $(HOST_CFLAGS) -c $< -o $@

$(BUILD_DIR)/$(TEST_DIR)/%: $(BUILD_DIR)/$(TEST_DIR)/%.o $(TARGET_SHARED)
	@echo "Linking test $@"
	@$(CC) $(HOST_CFLAGS) $< -L. -lflibc -Wl,-rpath=. -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET_STATIC) $(TARGET_SHARED) $(EXEC)
