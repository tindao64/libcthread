# libcthread - C Cooperative Threading Library

A simple and relatively portable cooperative threading library, written in C

## How to use in your project

Simply put the entire source tree where all the *.c files will get compiled, and include cthread.h.

## Supported platforms

GCC and similar compilers should be fine. These architectures will be supported:
- x86_64 SysV ABI
- aarch64 AAPCS64 ABI
- ARMv7E-M

## Porting

Port the things in arch.h if your platform isn't supported yet or the current support isn't OK.
The builtins use weak linkage, so you are free to override.
