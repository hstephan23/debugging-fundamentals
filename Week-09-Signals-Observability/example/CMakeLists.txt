# Week 9 — Logging, Tracing & Observability
#
#   cmake --build .           # build server and cpu_hog
#
# Practice ideas:
#   ./server &
#   strace -f -tt -e openat,read,write -p $(pgrep server)
#   perf record -g ./cpu_hog
#   perf report

cmake_minimum_required(VERSION 3.15)
project(week09_logging C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(COMMON_FLAGS -O2 -g -Wall -Wextra -Wpedantic -fno-omit-frame-pointer)

add_executable(server server.c)
target_compile_options(server PRIVATE ${COMMON_FLAGS})
# log.h is picked up automatically via #include since it lives next to server.c

add_executable(cpu_hog cpu_hog.c)
target_compile_options(cpu_hog PRIVATE ${COMMON_FLAGS})
# cpu_hog uses math.h; link libm explicitly (idempotent on macOS where it's in libc).
target_link_libraries(cpu_hog PRIVATE m)
