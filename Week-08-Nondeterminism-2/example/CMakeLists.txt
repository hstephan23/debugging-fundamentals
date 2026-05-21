# Week 8 — Concurrency II: Deadlocks & Live Thread Debugging
#
#   cmake --build .                    # plain builds
#   cmake --build . --target helgrind  # runs deadlock under helgrind
#
# For the classic two-lock deadlock:
#   ./deadlock           (will hang — Ctrl-C after a few seconds)
#   gdb -p $(pgrep deadlock)
#     (gdb) thread apply all bt
#
# Or under helgrind:
#   valgrind --tool=helgrind ./deadlock
#
# For the fixed version:
#   ./deadlock_fixed     (terminates normally)

cmake_minimum_required(VERSION 3.15)
project(week08_concurrency_2 C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(COMMON_FLAGS -O0 -g3 -Wall -Wextra -Wpedantic -fno-omit-frame-pointer)

set(TARGETS
    deadlock
    deadlock_fixed
    errorcheck_mutex
    cond_spurious)

foreach(t ${TARGETS})
    add_executable(${t} ${t}.c)
    target_compile_options(${t} PRIVATE ${COMMON_FLAGS})
    target_link_libraries(${t} PRIVATE Threads::Threads)
endforeach()

# --- helgrind: run the racy deadlock under helgrind -----------------------
add_custom_target(helgrind
    COMMAND valgrind --tool=helgrind $<TARGET_FILE:deadlock>
    DEPENDS deadlock
    USES_TERMINAL
    COMMENT "Running deadlock under helgrind")
