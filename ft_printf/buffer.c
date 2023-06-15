#include <unistd.h>
#include "ft_printf_private.h"
#include "ft_clib.h"

static void clear_buffer(buffer_t* buff) {
    ft_bzero(buff->buffer, PRINT_BUFFER_SIZE);
    buff->size = 0;
}

void flush_buffer_fd(buffer_t* buff) {
    if (write(buff->fd, buff->buffer, buff->size) != (ssize_t)buff->size) {
        buff->error = true;
    }
    clear_buffer(buff);
}

void flush_buffer_str(buffer_t* buff) {
    size_t i = 0;
    while (buff->str_index < buff->max_size && i < buff->size) {
        buff->str[buff->str_index++] = buff->buffer[i++];
    }

    clear_buffer(buff);
}

void add_to_buffer(buffer_t* buff, char c) {
    if (buff->size >= PRINT_BUFFER_SIZE) {
        buff->flusher(buff);
    }
    ++buff->ret;
    buff->buffer[buff->size++] = c;
}