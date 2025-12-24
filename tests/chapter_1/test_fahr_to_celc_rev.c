#include <stdarg.h>
#include <stddef.h>
#include <string.h>
#include <cmocka.h>

#include "chapter_1/fahr_to_celc_rev.h"

static void test_fahr_to_celc_rev_table_output(void **state) {
    (void)state;
    char buf[256];
    const char *expected =
        "*** Fahrenheit to Celsius Rev Conversion Table ***\n"
        "300  148.9\n"
        "280  137.8\n"
        "260  126.7\n"
        "240  115.6\n"
        "220  104.4\n"
        "200   93.3\n"
        "180   82.2\n"
        "160   71.1\n"
        "140   60.0\n"
        "120   48.9\n"
        "100   37.8\n"
        " 80   26.7\n"
        " 60   15.6\n"
        " 40    4.4\n"
        " 20   -6.7\n"
        "  0  -17.8\n";

    const size_t expected_len = strlen(expected);
    memset(buf, 0xA5, sizeof(buf));          // poison buffer
    size_t n = ch1_fahr_to_celc_rev_table(buf, sizeof(buf));

    assert_int_equal(n, expected_len);       // exact byte count
    assert_int_equal(buf[n], '\0');          // NUL terminator in bounds
    assert_memory_equal(buf, expected, expected_len + 1); // byte-for-byte incl NUL
}

size_t ch1_tests(struct CMUnitTest *out);

size_t ch1_fahr_to_celc_rev_tests(struct CMUnitTest *out) {
    out[0] = (struct CMUnitTest)cmocka_unit_test(test_fahr_to_celc_rev_table_output);
    return 1;
}
