#ifndef CLI_LIB_H
#define CLI_LIB_H

#include <stdio.h>
#include <stddef.h>
#include <stdarg.h>

static inline void cli_init(void) {

}

static inline void cli_clear(void) {
    printf("\x1b[2J\x1b[H");
}

static inline void cli_print(const char *s) {
    printf("%s", s);
}

static inline void cli_printf(const char *fmt, ... ) {
    va_list ap;
    va_start(ap, fmt);
    vprintf(fmt, ap);
    va_end(ap);
}

static inline char *cli_getline(char *buf, size_t size) {
    if (fgets(buf, (int)size, stdin) == NULL) return NULL;
    size_t len = 0;
    while (buf[len] != '\0') len++;
    if (len > 0 && buf[len-1] == '\n') buf[len-1] = '\0';
    return buf;
}

#endif