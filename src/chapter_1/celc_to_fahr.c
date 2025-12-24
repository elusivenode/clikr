#include "chapter_1/celc_to_fahr.h"
#include <stddef.h>
#include <stdio.h>

size_t ch1_celc_to_fahr_table(char *out, size_t out_len) {
    float fahr, celsius;
    int lower, upper, step;

    lower = 0;
    upper = 156;
    step = 12;

    celsius = lower;
    size_t used = 0;

    int written = snprintf(out + used, out_len - used,
                           "*** Celsius to Fahrenheit Conversion Table ***\n");
    if (written < 0 || (size_t)written >= out_len - used) return 0;
    used += (size_t)written;
    while (celsius <= upper) {
        fahr = celsius * (9.0 / 5.0) + 32;
        written = snprintf(out + used, out_len - used, "%3.0f %6.1f\n", celsius, fahr);

        if (written < 0) {
            return 0; // formatting error
        }
        if ((size_t)written >= out_len - used) {
            // buffer full / truncated
            return 0; // or return used for partial output
        }

        used += (size_t)written;
        celsius = celsius + step;
    }

    return used;
}
