# Week 2 — GDB Fundamentals
#
# Two small programs for practicing GDB basics:
#   fib      — recursive memoized Fibonacci (stepping, frames, args)
#   sleeper  — long-running process for `gdb -p PID` attach practice
#
# Suggested GDB session (after building):
#   gdb ./fib
#     (gdb) break fib
#     (gdb) run 10
#     (gdb) bt
#     (gdb) info args
#     (gdb) finish

cmake_minimum_required(VERSION 3.15)
project(week02_gdb_fundamentals C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(COMMON_FLAGS
    -O0 -g3 -Wall -Wextra -Wpedantic
    -fno-omit-frame-pointer)

add_executable(fib fib.c)
target_compile_options(fib PRIVATE ${COMMON_FLAGS})

add_executable(sleeper sleeper.c)
target_compile_options(sleeper PRIVATE ${COMMON_FLAGS})
