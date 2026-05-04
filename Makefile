CC := clang
AR := ar
ARFLAGS := rcs

OPT := -O3 -g0

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
  -ffreestanding -fno-builtin -nostdinc \
  -Iinclude $(OPT) $(WARN_CFLAGS)

# HOSTED (tests only)
HOST_CFLAGS := \
  -Iinclude $(OPT) $(WARN_CFLAGS)

SRC_DIR := src
TEST_DIR := tests
BUILD_DIR := build

TARGET := libflibc.a
EXEC := main

SRCS := $(shell find $(SRC_DIR) -name '*.c')
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

TEST_SRC := $(shell find $(TEST_DIR) -name '*.c')
TEST_OBJS := $(TEST_SRC:$(TEST_DIR)/%.c=$(BUILD_DIR)/$(TEST_DIR)/%.o)
TEST_OUT := $(TEST_SRC:$(TEST_DIR)/%.c=$(BUILD_DIR)/$(TEST_DIR)/%)

.PHONY: all clean tests check

all: $(TARGET) $(EXEC)

# LIBRARY (freestanding)
$(TARGET): $(OBJS)
	@echo "Archiving $@"
	@$(AR) $(ARFLAGS) $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "Compiling lib $<"
	@$(CC) $(FREESTANDING_CFLAGS) -c $< -o $@

# MAIN 
$(EXEC): main.c $(TARGET)
	@echo "Linking freestanding executable $@"
	@$(CC) \
	    $(FREESTANDING_CFLAGS) \
	    -nostdlib -nostartfiles \
	    -Wl,-e,_start \
	    main.c -L. -lflibc -o $@

# TESTS (HOSTED)
$(BUILD_DIR)/$(TEST_DIR)/%.o: $(TEST_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "Compiling test $<"
	@$(CC) $(HOST_CFLAGS) -c $< -o $@

$(BUILD_DIR)/$(TEST_DIR)/%: $(BUILD_DIR)/$(TEST_DIR)/%.o $(TARGET)
	@echo "Linking test $@"
	@$(CC) $(HOST_CFLAGS) $< -L. -lflibc -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET) $(EXEC)
