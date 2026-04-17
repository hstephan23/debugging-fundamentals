#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

int main(void)
{
    int nums[] = { 1, 2, 3, 4, 5 };
    size_t n = sizeof(nums) / sizeof(nums[0]);

    long expected = 1 + 2 + 3 + 4 + 5;  /* = 15 */
    long got = sum_array(nums, n);

    printf("expected=%ld got=%ld\n", expected, got);

    /* This assertion SHOULD pass for a correct sum_array. It often
     * doesn't, thanks to the deliberate off-by-one in utils.c reading
     * garbage memory past the array. */
    assert(got == expected);
    return 0;
}
