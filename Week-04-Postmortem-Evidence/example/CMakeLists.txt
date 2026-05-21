# Week 4 — Core Dumps & Postmortem
#
# Builds `crash` and `crash_handler`. Adds a `split` target that demonstrates
# the production pattern of stripping the binary and keeping a separate
# .debug file that gdb can still resolve symbols from.
#
# After building, enable core dumps in your shell:
#   ulimit -c unlimited
#   ./crash "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
#
# Then inspect:
#   gdb ./crash ./core          (or  coredumpctl gdb crash)
#     (gdb) bt
#     (gdb) frame 2
#     (gdb) info args
#     (gdb) info locals
#
# Split debuginfo demo:
#   cmake --build . --target split

cmake_minimum_required(VERSION 3.15)
project(week04_core_dumps C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(COMMON_FLAGS -O1 -g3 -Wall -Wextra -Wpedantic -fno-omit-frame-pointer)

add_executable(crash crash.c)
target_compile_options(crash PRIVATE ${COMMON_FLAGS})

# crash_handler uses backtrace_symbols + dladdr, so we need -rdynamic and -ldl
add_executable(crash_handler crash_handler.c)
target_compile_options(crash_handler PRIVATE ${COMMON_FLAGS})
target_link_options   (crash_handler PRIVATE -rdynamic)
target_link_libraries (crash_handler PRIVATE dl)

# --- Split debuginfo: strip binary, keep the .debug file alongside ---------
add_custom_target(split
    COMMAND objcopy --only-keep-debug $<TARGET_FILE:crash> $<TARGET_FILE:crash>.debug
    COMMAND strip --strip-debug $<TARGET_FILE:crash>
    COMMAND objcopy --add-gnu-debuglink=$<TARGET_FILE:crash>.debug $<TARGET_FILE:crash>
    COMMAND ${CMAKE_COMMAND} -E echo ""
    COMMAND ${CMAKE_COMMAND} -E echo "'file crash' now shows it as stripped, but gdb still finds symbols"
    COMMAND ${CMAKE_COMMAND} -E echo "via crash.debug in the same directory."
    DEPENDS crash
    USES_TERMINAL
    COMMENT "Stripping crash and producing a separate .debug file")
