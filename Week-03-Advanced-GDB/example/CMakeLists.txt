# Week 3 — Advanced GDB (watchpoints, scripting, rr)
#
# Builds watchpoint_demo and linked_list. Adds convenience targets for
# record-and-replay debugging with `rr`:
#   cmake --build . --target rr      # records a trace of watchpoint_demo
#   cmake --build . --target replay  # replay the most recent trace
#
# Recommended workflow for watchpoint_demo:
#   ./watchpoint_demo           (observe the bad final value of `secret`)
#   gdb ./watchpoint_demo
#     (gdb) break main
#     (gdb) run
#     (gdb) watch secret
#     (gdb) continue            (GDB stops at every write to `secret`)
#
# For reverse debugging:
#   cmake --build . --target rr
#   cmake --build . --target replay
#     (gdb) continue            (land at normal end)
#     (gdb) watch secret
#     (gdb) reverse-continue    (travels backward to the write you care about)

cmake_minimum_required(VERSION 3.15)
project(week03_advanced_gdb C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(COMMON_FLAGS -O0 -g3 -Wall -Wextra -Wpedantic -fno-omit-frame-pointer)

add_executable(watchpoint_demo watchpoint_demo.c)
target_compile_options(watchpoint_demo PRIVATE ${COMMON_FLAGS})

add_executable(linked_list linked_list.c)
target_compile_options(linked_list PRIVATE ${COMMON_FLAGS})

# --- rr record / replay -----------------------------------------------------
add_custom_target(rr
    COMMAND rr record $<TARGET_FILE:watchpoint_demo>
    DEPENDS watchpoint_demo
    USES_TERMINAL
    COMMENT "Recording an rr trace of watchpoint_demo")

add_custom_target(replay
    COMMAND rr replay
    USES_TERMINAL
    COMMENT "Replaying the most recent rr trace")
