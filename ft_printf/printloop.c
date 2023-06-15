#include <stdio.h>
#include "ft_clib.h"
#include "ft_printf_private.h"

void dbg_print_flags(flags_t flags) {
    fprintf(stderr, "alternate: %s\n", flags.alternate ? "true" : "false");
    fprintf(stderr, "zero: %s\n", flags.alternate ? "true" : "false");
    fprintf(stderr, "minus: %s\n", flags.alternate ? "true" : "false");
    fprintf(stderr, "space: %s\n", flags.alternate ? "true" : "false");
    fprintf(stderr, "plus: %s\n", flags.alternate ? "true" : "false");
    fprintf(stderr, "field_width: %lu\n", flags.field_width);
    fprintf(stderr, "precision: %lu\n", flags.precision);
}

void print_loop(buffer_t* buffer, const char* restrict format, va_list ap) {
    while (*format && buffer->error == false) {
        if (*format != '%') {
            add_to_buffer(buffer, *(format++));
            continue;
        }
        flags_t flags = gather_flags(buffer, format, ap);
    }
    flush(buffer);
}
