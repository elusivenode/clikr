#include "cli.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "examples.h"

static void print_usage(FILE *out) {
    fputs("usage:\n", out);
    fputs("  clikr                 interactive menu\n", out);
    fputs("  clikr list            list available examples\n", out);
    fputs("  clikr run <id>        run a specific example\n", out);
    fputs("  clikr help            show this help\n", out);
}

static void list_examples(FILE *out) {
    size_t i;
    for (i = 0; i < example_count(); i++) {
        const struct Example *ex = example_at(i);
        if (ex != NULL) {
            fprintf(out, "%s) %s\n", ex->alias, ex->id);
        }
    }
}

static int normalize_id(const char *in, char *out, size_t out_len) {
    size_t i = 0;
    if (out_len == 0) {
        return 0;
    }
    for (; in[i] != '\0'; i++) {
        if (i + 1 >= out_len) {
            return 0;
        }
        out[i] = (in[i] == '\\') ? '/' : in[i];
    }
    out[i] = '\0';
    return 1;
}

static int run_example_by_id(const char *raw_id) {
    char id[256];
    const struct Example *ex;

    if (!normalize_id(raw_id, id, sizeof(id))) {
        fputs("error: invalid example id\n", stderr);
        return 1;
    }
    ex = find_example(id);
    if (ex == NULL) {
        fprintf(stderr, "error: unknown example '%s'\n", id);
        return 1;
    }
    return ex->run();
}

static void trim_line(char *s) {
    size_t len = strlen(s);
    while (len > 0 && (s[len - 1] == '\n' || s[len - 1] == '\r')) {
        s[--len] = '\0';
    }
    while (*s != '\0' && isspace((unsigned char)*s)) {
        memmove(s, s + 1, strlen(s));
    }
    len = strlen(s);
    while (len > 0 && isspace((unsigned char)s[len - 1])) {
        s[--len] = '\0';
    }
}

static int run_menu(void) {
    char line[256];
    for (;;) {
        puts("Available examples:");
        list_examples(stdout);
        fputs("Select number, name, or 'q' to quit: ", stdout);
        if (fgets(line, sizeof(line), stdin) == NULL) {
            fputc('\n', stdout);
            return 0;
        }
        trim_line(line);
        if (line[0] == '\0') {
            continue;
        }
        if (strcmp(line, "q") == 0 || strcmp(line, "quit") == 0) {
            return 0;
        }
        if (strcmp(line, "l") == 0 || strcmp(line, "list") == 0) {
            continue;
        }
        if (isdigit((unsigned char)line[0]) && strchr(line, '.') == NULL) {
            char *end = NULL;
            long idx = strtol(line, &end, 10);
            if (end != line && idx > 0 && (size_t)idx <= example_count()) {
                const struct Example *ex = example_at((size_t)idx - 1);
                if (ex != NULL) {
                    (void)ex->run();
                }
                continue;
            }
        }
        (void)run_example_by_id(line);
    }
}

int cli_run(int argc, char **argv) {
    if (argc <= 1) {
        return run_menu();
    }
    if (strcmp(argv[1], "help") == 0 || strcmp(argv[1], "-h") == 0 ||
        strcmp(argv[1], "--help") == 0) {
        print_usage(stdout);
        return 0;
    }
    if (strcmp(argv[1], "list") == 0) {
        list_examples(stdout);
        return 0;
    }
    if (strcmp(argv[1], "run") == 0) {
        if (argc < 3) {
            fputs("error: missing example id\n", stderr);
            print_usage(stderr);
            return 1;
        }
        return run_example_by_id(argv[2]);
    }

    fputs("error: unknown command\n", stderr);
    print_usage(stderr);
    return 1;
}
