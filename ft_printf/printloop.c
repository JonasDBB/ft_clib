#include "ft_clib.h"
#include "ft_printf_private.h"

static flags_t gather_flags(buffer_t* buffer, const char* restrict format) {
    flags_t ret;
    ft_bzero(&ret, sizeof(flags_t));



    return ret;
}

void print_loop(buffer_t* buffer, const char* restrict format, va_list ap) {
    while (*format && buffer->error == false) {
        if (*format != '%') {
            add_to_buffer(buffer, *(format++));
            continue;
        }
        flags_t flags = gather_flags(buffer, format);
    }
}
