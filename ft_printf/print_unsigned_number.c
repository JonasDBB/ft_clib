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

static bool no_precision_zero(flags_t flags, size_t* len, unsigned long long n) {
    bool ret = false;
    if (n == 0 && flags.has_precision && flags.precision == 0) {
        --(*len);
        ret = true;
    }
    return ret;
}

static bool has_0x_prefix(flags_t flags, unsigned long long n) {
    if (flags.conversion == POINTER) {
        return true;
    }
    if (flags.alternate == true && n != 0 && (flags.conversion == HEX || flags.conversion == HEX_UPPER)) {
        return true;
    }
    return false;
}

void print_unr(buffer_t* buffer, flags_t flags, unsigned long long n, char nr_string[20]) {
    size_t len = ft_strlen(nr_string);
    size_t extra_precision = get_extra_precision(flags, &len);
    bool is_no_precision_zero = no_precision_zero(flags, &len, n);
    bool octal_zero = flags.conversion == OCTAL && flags.alternate && (n != 0 || is_no_precision_zero || flags.field_width);

    if (octal_zero) {
        ++len;
    }
    if (has_0x_prefix(flags, n)) {
        if (flags.field_width <= 2) {
            flags.field_width = 0;
        } else {
            flags.field_width -= 2;
        }
    }
    const char pad = flags.zero && n != 0 ? '0' : ' ';
    while (!flags.minus && len < flags.field_width) {
        add_to_buffer(buffer, pad);
        --flags.field_width;
    }

    if (octal_zero) {
        add_to_buffer(buffer, '0');
    }

    if (has_0x_prefix(flags, n)) {
        add_to_buffer(buffer, '0');
        add_to_buffer(buffer, flags.conversion == HEX_UPPER ? 'X' : 'x');
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
