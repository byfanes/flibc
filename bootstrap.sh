#!/bin/sh
set -e

echo "[1/2] Bootstrapping the build system..."
echo "[1/2] NOTE: This will took some time because it is single process..."

# We compile the CRT, all the library source files and build.c
# directly into a single executable called 'build'.
# This bypasses the need for an archive (.a) or shared object (.so) just to get started!

ARCH=$(uname -m)
C_FILES=$(find src -name '*.c')
ASM_FILES=$(find "src/arch/$ARCH/" -name '*.s')

clang -O0 -g3 \
    -ffreestanding -fno-builtin -nostdinc -nostdlib \
    -Iinclude -nostartfiles \
    -Wl,-e,_start \
    $C_FILES $ASM_FILES build.c \
    -o build

echo $C_FILES $ASM_FILES
echo "[2/2] Bootstrap complete. Running build..."
./build
