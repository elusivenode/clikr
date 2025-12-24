#include <stdarg.h>
#include <stddef.h>
#include <string.h>
#include <cmocka.h>

#include "chapter_1/temp_conv.h"

static void test_temp_conv_table_output(void **state) {
    (void)state;
    char buf[256];
    const char *expected =
        "0\t-17\n"
        "20\t-6\n"
        "40\t4\n"
        "60\t15\n"
        "80\t26\n"
        "100\t37\n"
        "120\t48\n"
        "140\t60\n"
        "160\t71\n"
        "180\t82\n"
        "200\t93\n"
        "220\t104\n"
        "240\t115\n"
        "260\t126\n"
        "280\t137\n"
        "300\t148\n";

    const size_t expected_len = strlen(expected);
    memset(buf, 0xA5, sizeof(buf));          // poison buffer
    size_t n = ch1_temp_conv_table(buf, sizeof(buf));

    assert_int_equal(n, expected_len);       // exact byte count
    assert_int_equal(buf[n], '\0');          // NUL terminator in bounds
    assert_memory_equal(buf, expected, expected_len + 1); // byte-for-byte incl NUL
}

size_t ch1_tests(struct CMUnitTest *out);

size_t ch1_temp_conv_tests(struct CMUnitTest *out) {
    out[0] = (struct CMUnitTest)cmocka_unit_test(test_temp_conv_table_output);
    return 1;
}
