#include "ft_printf_private.h"
#include "ft_clib.h"

static size_t get_extra_precision(flags_t flags, size_t* len, long long n) {
    size_t ret = 0;
    if (*len < flags.precision) {
        ret = flags.precision - *len;
        if (n < 0) {
            ++ret;
        }
        *len = flags.precision;
    }
    return ret;
}

static char prepend_char(flags_t flags, long long n) {
    char ret = -1;
    if (n >= 0 && (flags.plus || flags.space)) {
        if (flags.plus) {
            ret = '+';
        } else if (flags.space) {
            ret = ' ';
        }
    }

    if (n < 0) {
        ret = '-';
    }

    return ret;
}

static bool no_precision_zero(flags_t flags, size_t* len, long long n) {
    bool ret = false;
    if (n == 0 && flags.has_precision && flags.precision == 0) {
        --(*len);
        ret = true;
    }
    return ret;
}

void print_nr(buffer_t* buffer, flags_t flags, long long n, char nr_string[20]) {
    size_t len = ft_strlen(nr_string);
    size_t extra_precision = get_extra_precision(flags, &len, n);
    char prepend = prepend_char(flags, n);
    bool is_no_precision_zero = no_precision_zero(flags, &len, n);

    if (prepend != -1) {
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

    while (extra_precision-- != 0) {
        add_to_buffer(buffer, '0');
    }

    // - is alerady prepended to make sure it is printed before extra 0s from precision
    size_t i = prepend == '-' ? 1 : 0;
    for (; nr_string[i] && !is_no_precision_zero; ++i) {
        add_to_buffer(buffer, nr_string[i]);
    }

    while (flags.minus && len < flags.field_width) {
        add_to_buffer(buffer, ' ');
        --flags.field_width;
    }
}
