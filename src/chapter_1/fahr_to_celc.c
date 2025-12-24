#include "chapter_1/fahr_to_celc.h"
#include <stddef.h>
#include <stdio.h>

size_t ch1_fahr_to_celc_table(char *out, size_t out_len) {
    float fahr, celsius;
    int lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;

    fahr = lower;
    size_t used = 0;

    int written = snprintf(out + used, out_len - used,
                           "*** Fahrenheit to Celsius Conversion Table ***\n");
    if (written < 0 || (size_t)written >= out_len - used) return 0;
    used += (size_t)written;
    while (fahr <= upper) {
        celsius = (5.0 / 9.0) * (fahr - 32);
        written = snprintf(out + used, out_len - used, "%3.0f %6.1f\n", fahr, celsius);

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
