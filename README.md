# flibc

A custom C library to fix C's historical flaws. Written in C89 without relying compiler-specific extensions and (trying to) avoiding macro-slop.

> **Note:** This library is a work in progress and currently on supports x86_64 Linux.

## Repos

Github(Mirror): https://github.com/byfanes/flibc
Codeberg(Actual work done here): https://codeberg.org/fanes/flibc

## Why does it exist?

> **No Hidden/Gobal State:** The standard libc forces users to rely on hidden global state (like 'errno' or 'stdin'), which can be painful and unsafe to debug/work while using multithreading.

> **Builtin Data Structures:** Every C developer eventually implements their own slice or dynamic array. By providing these basic types directly in the library, 'flibc' speeds up development and prevents reinventing the wheel.

> **Explicit Error Handling:** IF there is an error, functions just return an 'error_t' instead of crashing or modifying a global variable.

> **A Modern C Runtime:** The C runtime parses arguments into slices. Your program receives explicit parameters for standard stream, the executable name, cli arguments and the standard allocator.

## Example Usage

You can find some examples in 'examples/' folder.
