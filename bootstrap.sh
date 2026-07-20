#!/bin/sh
set -e

echo "[1/3] Bootstrapping the build system..."
echo "[1/3] NOTE: This will took some time because it is single process..."

# We compile the CRT, all the library source files and build.c
# directly into a single executable called 'build'.
# This bypasses the need for an archive (.a) or shared object (.so) just to get started!

ARCH=$(uname -m)
C_FILES=$(find src -name '*.c')
ASM_FILES=$(find "src/arch/$ARCH/" -name '*.s')

gcc -O0 -g3  \
      -fsanitize=undefined -fsanitize-trap=undefined \
      -Wall -Wextra -Wpedantic \
      -Wconversion -Wsign-conversion \
      -Wformat -Wformat-overflow -Wformat-truncation \
      -Wstrict-prototypes -Wmissing-prototypes \
      -Wshadow -Wpointer-arith \
      -Wwrite-strings -Wundef \
      -Wfloat-equal -Wcast-align -Wno-int-conversion \
      -Wswitch-default -std=c89 -pedantic -Werror \
      -ffreestanding -fno-builtin -nostdinc -nostdlib \
      -Wno-overlength-strings -Iinclude -nostartfiles \
      -Wl,-e,_start \
      $C_FILES $ASM_FILES build.c \
      -o build

echo $C_FILES $ASM_FILES
echo "[2/3] Bootstrap complete. Running build..."
./build -b -g
echo "[3/3] Build completed! Now installing the library to system"
sudo cp .build/flibc.* /usr/lib
sudo cp include/* /usr/include/flibc/
