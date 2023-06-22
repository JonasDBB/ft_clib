#include <stdio.h>
#include "ft_clib.h"
#include "ft_printf_private.h"

const char* const bool_str[] = {
    [false] = "false",
    [true] = "true"
};

const char* const l_name[] = {
        [NONE] = "NONE",
        [HH] = "HH",
        [H] = "H",
        [L] = "L",
        [LL] = "LL",
        [J] = "J",
        [T] = "T",
        [Z] = "Z"
};

static void dbg_print_flags(flags_t flags) {
    fprintf(stderr, "alternate: %s\n", bool_str[flags.alternate]);
    fprintf(stderr, "zero: %s\n", bool_str[flags.zero]);
    fprintf(stderr, "minus: %s\n", bool_str[flags.minus]);
    fprintf(stderr, "space: %s\n", bool_str[flags.space]);
    fprintf(stderr, "plus: %s\n", bool_str[flags.plus]);
    fprintf(stderr, "field_width: %lu\n", flags.field_width);
    fprintf(stderr, "precision: %lu\n", flags.precision);
    fprintf(stderr, "length mod: %s\n", l_name[flags.length_mod]);
}

void print_loop(buffer_t* buffer, const char* restrict* format, va_list ap) {
    const char* restrict fmt = *format;
    while (*fmt && buffer->error == false) {
        if (*fmt != '%') {
            add_to_buffer(buffer, *(fmt++));
            continue;
        }
        ++fmt;
        flags_t flags = gather_flags(buffer, &fmt, ap);
        dbg_print_flags(flags);
    }
    flush(buffer);
}
