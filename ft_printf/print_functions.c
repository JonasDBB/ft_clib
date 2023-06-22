#include "ft_printf_private.h"

void digit(buffer_t* buffer, flags_t flags, va_list ap) {
    UNUSED buffer;
    UNUSED flags;
    UNUSED ap;
}

void octal(buffer_t* buffer, flags_t flags, va_list ap) {
    UNUSED buffer;
    UNUSED flags;
    UNUSED ap;
}

void unsigned_int(buffer_t* buffer, flags_t flags, va_list ap) {
    UNUSED buffer;
    UNUSED flags;
    UNUSED ap;
}

void hex(buffer_t* buffer, flags_t flags, va_list ap) {
    UNUSED buffer;
    UNUSED flags;
    UNUSED ap;
}

void hex_upper(buffer_t* buffer, flags_t flags, va_list ap) {
    UNUSED buffer;
    UNUSED flags;
    UNUSED ap;
}

void character(buffer_t* buffer, flags_t flags, va_list ap) {
    UNUSED buffer;
    UNUSED flags;
    UNUSED ap;
}

void string(buffer_t* buffer, flags_t flags, va_list ap) {
    UNUSED buffer;
    UNUSED flags;
    UNUSED ap;
}

void pointer(buffer_t* buffer, flags_t flags, va_list ap) {
    UNUSED buffer;
    UNUSED flags;
    UNUSED ap;
}

void percent(buffer_t* buffer, flags_t flags, va_list ap) {
    UNUSED flags;
    UNUSED ap;
    add_to_buffer(buffer, '%');
}
