#include <stdarg.h>
#include <stddef.h>
#include <string.h>
#include <cmocka.h>

#include "chapter_1/celc_to_fahr.h"

static void test_celc_to_fahr_table_output(void **state) {
    (void)state;
    char buf[256];
    const char *expected =
        "*** Celsius to Fahrenheit Conversion Table ***\n"
        "  0   32.0\n"
        " 12   53.6\n"
        " 24   75.2\n"
        " 36   96.8\n"
        " 48  118.4\n"
        " 60  140.0\n"
        " 72  161.6\n"
        " 84  183.2\n"
        " 96  204.8\n"
        "108  226.4\n"
        "120  248.0\n"
        "132  269.6\n"
        "144  291.2\n"
        "156  312.8\n";

    const size_t expected_len = strlen(expected);
    memset(buf, 0xA5, sizeof(buf));          // poison buffer
    size_t n = ch1_celc_to_fahr_table(buf, sizeof(buf));

    assert_int_equal(n, expected_len);       // exact byte count
    assert_int_equal(buf[n], '\0');          // NUL terminator in bounds
    assert_memory_equal(buf, expected, expected_len + 1); // byte-for-byte incl NUL
}

size_t ch1_tests(struct CMUnitTest *out);

size_t ch1_celc_to_fahr_tests(struct CMUnitTest *out) {
    out[0] = (struct CMUnitTest)cmocka_unit_test(test_celc_to_fahr_table_output);
    return 1;
}
