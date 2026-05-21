#include "utils.h"

/*
 * BUG (intentional): loop condition uses <= instead of <, so we read one past
 * the end of the array. On a debug build you may "get away with it"; on a
 * release build the compiler may hoist or reorder things in ways that make
 * the symptom different.
 *
 * Exercise:
 *   1. Diagnose this WITHOUT a debugger — only by re-reading, adding
 *      asserts, and printing state. Time yourself.
 *   2. Log what tipped you off in ../bug-journal.md.
 *   3. Fix the loop bound; confirm both debug and release builds agree.
 */
long sum_array(const int *arr, size_t n)
{
    long total = 0;
    for (size_t i = 0; i <= n; i++) {   /* <-- off-by-one here */
        total += arr[i];
    }
    return total;
}
