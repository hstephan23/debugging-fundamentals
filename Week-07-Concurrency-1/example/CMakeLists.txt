# Week 7 — Concurrency I: Data Races & ThreadSanitizer
#
# Plain builds of four small programs, plus a ThreadSanitizer build of the
# racy counter (tsan_race).
#
#   cmake --build .
#
#   ./race_counter           (run a few times — note the varying results)
#   ./race_counter_mutex     (always 2_000_000)
#   ./race_counter_atomic    (always 2_000_000)
#   ./false_sharing          (observe per-cache-line slowdown)
#   ./tsan_race              (TSan reports the race with full stacks)

cmake_minimum_required(VERSION 3.15)
project(week07_concurrency_1 C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(COMMON_FLAGS -O1 -g3 -Wall -Wextra -Wpedantic -fno-omit-frame-pointer)

set(PLAIN_TARGETS
    race_counter
    race_counter_mutex
    race_counter_atomic
    false_sharing)

foreach(t ${PLAIN_TARGETS})
    add_executable(${t} ${t}.c)
    target_compile_options(${t} PRIVATE ${COMMON_FLAGS})
    target_link_libraries(${t} PRIVATE Threads::Threads)
endforeach()

# --- tsan_race: same source as race_counter, under ThreadSanitizer --------
add_executable(tsan_race race_counter.c)
target_compile_options(tsan_race PRIVATE ${COMMON_FLAGS} -fsanitize=thread)
target_link_options   (tsan_race PRIVATE -fsanitize=thread)
target_link_libraries (tsan_race PRIVATE Threads::Threads)
