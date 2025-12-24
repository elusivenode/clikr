#include "chapter_1/temp_conv.h"
#include <stdio.h>

size_t ch1_temp_conv_table(char *out, size_t out_len) {
    int fahr, celsius;
    int lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;

    fahr = lower;
    size_t used = 0;

    while (fahr <= upper) {
        celsius = 5 * (fahr - 32) / 9;
        int written = snprintf(out + used, out_len - used, "%d\t%d\n", fahr, celsius);

        if (written < 0) {
            return 0; // formatting error
        }
        if ((size_t)written >= out_len - used) {
            // buffer full / truncated
            return 0; // or return used for partial output
        }

        used += (size_t)written;
        fahr = fahr + step;
    }

    return used;
}
