#include <unistd.h>
#include "ft_printf_private.h"
#include "ft_clib.h"

static void clear_buffer(buffer_t* buff) {
    ft_bzero(buff->buffer, PRINT_BUFFER_SIZE);
    buff->buffer_size = 0;
}

static void flush_buffer_fd(buffer_t* buff) {
    if (write(buff->fd, buff->buffer, buff->buffer_size) != (ssize_t)buff->buffer_size) {
        buff->error = true;
    }
}

static void flush_buffer_str(buffer_t* buff) {
    size_t i = 0;
    while (buff->str_data.str_index < buff->str_data.max_size && i < buff->buffer_size) {
        buff->str_data.str[buff->str_data.str_index++] = buff->buffer[i++];
    }
}

void flush(buffer_t* buff) {
    if (buff->is_string == true) {
        flush_buffer_str(buff);
    } else {
        flush_buffer_fd(buff);
    }
    clear_buffer(buff);
}

void add_to_buffer(buffer_t* buff, char c) {
    if (buff->buffer_size >= PRINT_BUFFER_SIZE) {
        flush(buff);
    }
    ++buff->ret;
    buff->buffer[buff->buffer_size++] = c;
}

void terminate_string_buffer(buffer_t* buff) {
    if (buff->is_string) {
        buff->str_data.str[buff->str_data.str_index++] = '\0';
    }
}