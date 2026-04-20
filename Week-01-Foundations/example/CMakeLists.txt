# Week 1 — Foundations & Methodology
#
# Two executables from the same sources, compiled with different flags:
#   sum_debug   — unoptimized, full debug info, loud warnings
#   sum_release — optimized, same source, may behave differently!
#
# The point is to internalize that *the same source* can behave differently
# depending on how you compile it. Debug is for understanding; release is
# for shipping.
#
# In CLion: both targets appear in the run configurations dropdown.
#
# From the command line (inside build/):
#   cmake -S .. -B .
#   cmake --build . --target sum_debug
#   cmake --build . --target sum_release
#   cmake --build . --target run-debug
#   cmake --build . --target run-release

cmake_minimum_required(VERSION 3.15)
project(week01_foundations C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCES main.c utils.c)

set(WARN_FLAGS
    -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wformat=2
    -fno-omit-frame-pointer)

# --- Debug build -----------------------------------------------------------
add_executable(sum_debug ${SOURCES})
target_compile_options(sum_debug PRIVATE
    ${WARN_FLAGS} -O0 -g3 -fno-common -D_FORTIFY_SOURCE=0)

# --- Release build ---------------------------------------------------------
add_executable(sum_release ${SOURCES})
target_compile_options(sum_release PRIVATE
    ${WARN_FLAGS} -O2 -g -DNDEBUG)

# --- Convenience "run" targets --------------------------------------------
add_custom_target(run-debug
    COMMAND $<TARGET_FILE:sum_debug>
    DEPENDS sum_debug
    USES_TERMINAL)

add_custom_target(run-release
    COMMAND $<TARGET_FILE:sum_release>
    DEPENDS sum_release
    USES_TERMINAL)
