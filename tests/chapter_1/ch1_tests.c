#include <stdarg.h>
#include <stddef.h>
#include <cmocka.h>

size_t ch1_hello_world_tests(struct CMUnitTest *out);
size_t ch1_temp_conv_tests(struct CMUnitTest *out);

size_t ch1_tests(struct CMUnitTest *out) {
    size_t count = 0;
    count += ch1_hello_world_tests(out + count);
    count += ch1_temp_conv_tests(out + count);
    return count;
}
