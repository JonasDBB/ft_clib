#include "ft_printf_private.h"
#include "ft_clib.h"

static size_t get_extra_precision(flags_t flags, size_t* len) {
    size_t ret = 0;
    if (*len < flags.precision) {
        ret = flags.precision - *len;
        *len = flags.precision;
    }
    return ret;
}

static char prepend_char(flags_t flags, size_t* len) {
    char ret = -1;
    if (flags.plus || flags.space) {
        ++(*len);
        if (flags.plus) {
            ret = '+';
        } else if (flags.space) {
            ret = ' ';
        }
    }

    return ret;
}

static bool no_precision_zero(flags_t flags, size_t* len, unsigned long long n) {
    bool ret = false;
    if (n == 0 && flags.has_precision && flags.precision == 0) {
        --(*len);
        ret = true;
    }
    return ret;
}

void print_unr(buffer_t* buffer, flags_t flags, unsigned long long n, char nr_string[20]) {
    size_t len = ft_strlen(nr_string);
    size_t extra_precision = get_extra_precision(flags, &len);
    char prepend = prepend_char(flags, &len);
    bool is_no_precision_zero = no_precision_zero(flags, &len, n);
    bool octal_zero = flags.conversion == OCTAL && flags.alternate && (n != 0 || is_no_precision_zero || flags.field_width);

    if (octal_zero) {
        ++len;
    }
    const char pad = flags.zero && n != 0 ? '0' : ' ';
    while (!flags.minus && len < flags.field_width) {
        add_to_buffer(buffer, pad);
        --flags.field_width;
    }

    if (prepend != -1) {
        add_to_buffer(buffer, prepend);
    }

    if (octal_zero) {
        add_to_buffer(buffer, '0');
    }

    while (extra_precision-- != 0) {
        add_to_buffer(buffer, '0');
    }

    for (size_t i = 0; nr_string[i] && !is_no_precision_zero; ++i) {
        add_to_buffer(buffer, nr_string[i]);
    }

    while (flags.minus && len < flags.field_width) {
        add_to_buffer(buffer, ' ');
        --flags.field_width;
    }
}