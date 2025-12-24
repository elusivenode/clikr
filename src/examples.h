#ifndef EXAMPLES_H
#define EXAMPLES_H

#include <stddef.h>

struct Example {
    const char *alias;
    const char *id;
    const char *label;
    int (*run)(void);
};

size_t example_count(void);
const struct Example *example_at(size_t index);
const struct Example *find_example(const char *id);

#endif
