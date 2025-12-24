#include "chapter_1/fahr_to_celc_rev.h"
#include <stddef.h>
#include <stdio.h>

size_t ch1_fahr_to_celc_rev_table(char *out, size_t out_len) {
    int fahr;
    size_t used = 0;

    int written = snprintf(out + used, out_len - used,
                           "*** Fahrenheit to Celsius Rev Conversion Table ***\n");
    if (written < 0 || (size_t)written >= out_len - used) return 0;
    used += (size_t)written;
    for (fahr = 300; fahr >= 0; fahr -= 20) {
        written = snprintf(out + used, out_len - used, "%3d %6.1f\n", fahr, (5.0 / 9.0) * (fahr - 32));

        if (written < 0) {
            return 0; // formatting error
        }
        if ((size_t)written >= out_len - used) {
            // buffer full / truncated
            return 0; // or return used for partial output
        }
        used += (size_t)written;
    }
    return used;
}
