#include <stdarg.h>
#include <stddef.h>
#include <cmocka.h>

#include "chapter_1/hello_world.h"

static void test_hello_world_string(void **state) {
    (void)state;
    assert_string_equal(ch1_hello_world(), "hello, world\n");
}

size_t ch1_hello_world_tests(struct CMUnitTest *out) {
    out[0] = (struct CMUnitTest)cmocka_unit_test(test_hello_world_string);
    return 1;
}
