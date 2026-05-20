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

FREESTANDING_CFLAGS := \
  -ffreestanding -fno-builtin -nostdinc -nostdlib \
  -Iinclude $(OPT) $(WARN_CFLAGS)

TARGET_STATIC := libflibc.a
TARGET_SHARED := libflibc.so

ARCH ?= $(shell uname -m)
SRC_DIR := src
ASM_DIR := $(SRC_DIR)/arch/$(ARCH)
TEST_DIR := tests
EXM_DIR := examples
BUILD_DIR := build
BUILD_EXM_DIR := build_examples
BUILD_C_DIR := build/c
BUILD_ASM_DIR := build/asm

C_SRC := $(shell find $(SRC_DIR) -name '*.c')
ASM_SRC_ALL := $(shell find $(ASM_DIR) -name '*.S')
CRT0_SRC := $(shell find $(ASM_DIR) -name 'crt0.S')
ASM_SRC := $(filter-out $(CRT0_SRC),$(ASM_SRC_ALL))
TEST_SRC := $(shell find $(TEST_DIR) -name '*.c')
EXM_SRC := $(shell find $(EXM_DIR) -name '*.c')

C_OBJ := $(C_SRC:$(SRC_DIR)/%.c=$(BUILD_C_DIR)/%.o)
CRT0_OBJ := $(CRT0_SRC:$(SRC_DIR)/%.S=$(BUILD_DIR)/%.o)
ASM_OBJ := $(ASM_SRC:$(SRC_DIR)/%.S=$(BUILD_ASM_DIR)/%.o)
TEST_OBJS := $(TEST_SRC:$(TEST_DIR)/%.c=$(BUILD_DIR)/$(TEST_DIR)/%.o)

EXM_OUT := $(EXM_SRC:$(EXM_DIR)/%.c=$(BUILD_EXM_DIR)/%)
TEST_OUT := $(TEST_SRC:$(TEST_DIR)/%.c=$(BUILD_DIR)/$(TEST_DIR)/%)

.PHONY: all clean tests check main

all: $(TARGET_STATIC) $(TARGET_SHARED)

main: main.c $(CRT0_OBJ) $(TARGET_SHARED)
	@echo "Linking freestanding executable $@"
	@$(CC) \
	    $(FREESTANDING_CFLAGS) \
	    -nostdlib -nostartfiles \
	    -Wl,-e,_start \
	    $(CRT0_OBJ) main.c -L. -lflibc -Wl,-rpath=. -o $@

clean:
	rm -rf $(BUILD_EXM_DIR) $(BUILD_DIR) $(TARGET_STATIC) $(TARGET_SHARED) $(EXEC)

examples: $(EXM_OUT)

tests: $(TEST_OUT)

check: tests
	@echo "--- Running Tests ---"
	@for test in $(TEST_OUT); do \
		echo "Running $$test..."; \
		./$$test || exit 1; \
	done
	@echo "--- All tests passed! ---"


$(TARGET_STATIC): $(C_OBJ) $(ASM_OBJ)
	@echo "Archiving $@"
	@$(AR) $(ARFLAGS) $@ $^

$(TARGET_SHARED): $(C_OBJ) $(ASM_OBJ)
	@echo "Linking shared library $@"
	@$(CC) -shared -nostdlib -fPIC -o $@ $^

$(BUILD_C_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "Compiling lib $<"
	@$(CC) $(FREESTANDING_CFLAGS) -c $< -o $@

$(BUILD_ASM_DIR)/%.o: $(SRC_DIR)/%.S
	@mkdir -p $(dir $@)
	@echo "Compiling lib $<"
	@$(CC) $(FREESTANDING_CFLAGS) -c $< -o $@

$(CRT0_OBJ): $(CRT0_SRC)
	@mkdir -p $(dir $@)
	@echo "Compiling crt $<"
	@$(CC) $(FREESTANDING_CFLAGS) -c $< -o $@

$(BUILD_DIR)/$(TEST_DIR)/%.o: $(TEST_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "Compiling test $<"
	@$(CC) $(FREESTANDING_CFLAGS) -c $< -o $@

$(BUILD_DIR)/$(TEST_DIR)/%: $(BUILD_DIR)/$(TEST_DIR)/%.o $(TARGET_SHARED) $(CRT0_OBJ)
	@echo "Linking test $@"
	@$(CC) $(FREESTANDING_CFLAGS) -nostartfiles -Wl,-e,_start \
		$(CRT0_OBJ) $< -L. -lflibc -Wl,-rpath=. -o $@

$(BUILD_EXM_DIR)/%: $(EXM_DIR)/%.c $(TARGET_SHARED) $(CRT0_OBJ)
	@mkdir -p $(dir $@)
	@cp $(TARGET_SHARED) $(BUILD_EXM_DIR)
	@echo "Compiling examples $<"
	@$(CC) $(FREESTANDING_CFLAGS) -nostartfiles -Wl,-e,_start \
		$(CRT0_OBJ) $< -L. -lflibc -Wl,-rpath=. -o $@
