# Week 6 — Sanitizers (ASan, UBSan, LSan)
#
# Two small demos compiled under different sanitizers so you can see what
# each one catches.
#
#   asan_demo   -> AddressSanitizer; LeakSanitizer where supported
#   ubsan_demo  -> UBSanitizer only
#
#   cmake --build .
#   ./asan_demo
#   ./ubsan_demo

cmake_minimum_required(VERSION 3.15)
project(week06_sanitizers C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(COMMON_FLAGS -O1 -g3 -Wall -Wextra -Wpedantic -fno-omit-frame-pointer)

# --- asan_demo: ASan, plus LSan on platforms that support it --------------
add_executable(asan_demo asan_demo.c)
target_compile_options(asan_demo PRIVATE
    ${COMMON_FLAGS}
    -fsanitize=address -fno-sanitize-recover=all)
target_link_options(asan_demo PRIVATE
    -fsanitize=address)

# --- ubsan_demo: UBSan only -----------------------------------------------
add_executable(ubsan_demo ubsan_demo.c)
target_compile_options(ubsan_demo PRIVATE
    ${COMMON_FLAGS}
    -fsanitize=undefined -fno-sanitize-recover=undefined)
target_link_options(ubsan_demo PRIVATE
    -fsanitize=undefined)
