#include "ft_printf_private.h"
#include "ft_clib.h"

void print_string(buffer_t* buffer, flags_t flags, char* string) {
    size_t len = ft_strlen(string);
    if (flags.has_precision && flags.precision < len) {
        len = flags.precision;
    }

    size_t padding_amnt = 0;
    if (flags.field_width > len) {
        padding_amnt = flags.field_width - len;
    }

    while (padding_amnt && !flags.minus) {
        add_to_buffer(buffer, ' ');
        --padding_amnt;
    }

    for (size_t i = 0; i < len; ++i) {
        add_to_buffer(buffer, string[i]);
    }

    while (padding_amnt && flags.minus) {
        add_to_buffer(buffer, ' ');
        --padding_amnt;
    }
}
