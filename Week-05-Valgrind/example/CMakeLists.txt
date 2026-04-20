# Week 5 — Memory Bugs with Valgrind
#
# A "bug buffet" — one tiny program per bug class. Build everything, then
# run each under Memcheck.
#
#   cmake --build .
#   valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./01_heap_overflow
#   valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./02_use_after_free
#   ...
#
# Or:
#   cmake --build . --target check-all    # runs valgrind on every target
#
# Predict what Memcheck will say BEFORE running. That's the exercise.

cmake_minimum_required(VERSION 3.15)
project(week05_valgrind C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(COMMON_FLAGS -O0 -g3 -Wall -Wextra -Wpedantic -fno-omit-frame-pointer)

set(DEMO_TARGETS
    01_heap_overflow
    02_use_after_free
    03_double_free
    04_uninitialized
    05_missing_nul
    06_off_by_one_write
    07_leak
    08_stack_use_after_return)

foreach(t ${DEMO_TARGETS})
    add_executable(${t} ${t}.c)
    target_compile_options(${t} PRIVATE ${COMMON_FLAGS})
endforeach()

# --- check-all: run every binary under memcheck ---------------------------
set(VALGRIND_FLAGS
    --leak-check=full --show-leak-kinds=all
    --track-origins=yes --error-exitcode=1)

# Build a list of COMMAND invocations — one per target.
set(_valgrind_cmds "")
foreach(t ${DEMO_TARGETS})
    list(APPEND _valgrind_cmds
        COMMAND ${CMAKE_COMMAND} -E echo ""
        COMMAND ${CMAKE_COMMAND} -E echo "===== ${t} ====="
        COMMAND valgrind ${VALGRIND_FLAGS} $<TARGET_FILE:${t}> || true)
endforeach()

add_custom_target(check-all
    ${_valgrind_cmds}
    DEPENDS ${DEMO_TARGETS}
    USES_TERMINAL
    COMMENT "Running every demo under valgrind memcheck")
