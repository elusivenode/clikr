#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

// Declare each chapter’s test collector.
size_t ch1_tests(struct CMUnitTest *out);

int main(void) {
    struct CMUnitTest tests[128];
    size_t count = 0;

    // Collect chapter 1 tests.
    count += ch1_tests(tests + count);
    return _cmocka_run_group_tests("clikr_tests", tests, count, NULL, NULL);
}
