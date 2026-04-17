#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>

/*
 * sum_array: add up n ints from arr.
 *
 * NOTE: this function has a deliberate off-by-one bug so you can practice
 * diagnosing it *without* a debugger in Week 1. Fix it in Week 2 after
 * learning GDB.
 */
long sum_array(const int *arr, size_t n);

#endif /* UTILS_H */
