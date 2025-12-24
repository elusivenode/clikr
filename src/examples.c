#include "examples.h"

#include <stdio.h>
#include <string.h>

#include "chapter_1/hello_world.h"
#include "chapter_1/fahr_to_celc.h"
#include "chapter_1/celc_to_fahr.h"

static int run_ch1_hello_world(void) {
    fputs(ch1_hello_world(), stdout);
    return 0;
}

static int run_ch1_fahr_to_celc(void) {
    char buf[256];
    size_t n = ch1_fahr_to_celc_table(buf, sizeof(buf));
    if (n == 0 || n >= sizeof(buf)) {
        fputs("error: temp conversion table did not fit buffer\n", stderr);
        return 1;
    }
    fputs(buf, stdout);
    return 0;
}

static int run_ch1_celc_to_fahr(void) {
    char buf[256];
    size_t n = ch1_celc_to_fahr_table(buf, sizeof(buf));
    if (n == 0 || n >= sizeof(buf)) {
        fputs("error: temp conversion table did not fit buffer\n", stderr);
        return 1;
    }
    fputs(buf, stdout);
    return 0;
}

static const struct Example k_examples[] = {
    { "1.1", "chapter_1/hello_world", "Hello, world", run_ch1_hello_world },
    { "1.2", "chapter_1/fahr_to_celc", "Fahrenheit-Celsius table", run_ch1_fahr_to_celc },
    { "1.3", "chapter_1/celc_to_fahr", "Celsius-Fahrenheit table", run_ch1_celc_to_fahr },
};

size_t example_count(void) {
    return sizeof(k_examples) / sizeof(k_examples[0]);
}

const struct Example *example_at(size_t index) {
    if (index >= example_count()) {
        return NULL;
    }
    return &k_examples[index];
}

const struct Example *find_example(const char *id) {
    size_t i;
    for (i = 0; i < example_count(); i++) {
        if (strcmp(k_examples[i].id, id) == 0 ||
            strcmp(k_examples[i].alias, id) == 0) {
            return &k_examples[i];
        }
    }
    return NULL;
}
