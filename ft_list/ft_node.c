#include <errno.h>
#include <stdlib.h>
#include "ft_list.h"

node_t* new_node(void* data) {
    node_t* ret = malloc(sizeof(node_t));
    if (!ret) {
        return NULL;
    }
    ret->next = NULL;
    ret->prev = NULL;
    ret->data = data;
    return ret;
}

void remove_from_list(node_t* node) {
    if (!node) {
        errno = EINVAL;
        return;
    }
    if (node->next) {
        node->next->prev = node->prev;
    }
    if (node->prev) {
        node->prev->next = node->next;
    }
    node->next = NULL;
    node->prev = NULL;
}

void delete_node(node_t* node, void (* deleter)(void*)) {
    if (!node) {
        errno = EINVAL;
        return;
    }
    remove_from_list(node);
    if (node->data && deleter) {
        deleter(node->data);
    }
    free(node);
}

bool insert_node_after(node_t* to_insert, node_t* dest) {
    if (!to_insert || !dest) {
        errno = EINVAL;
        return false;
    }
    if (to_insert->next || to_insert->prev) {
        remove_from_list(to_insert);
    }
    if (dest->next) {
        to_insert->next = dest->next;
        dest->next->prev = to_insert;
    }
    dest->next = to_insert;
    to_insert->prev = dest;
    return true;
}

bool insert_node_before(node_t* to_insert, node_t* dest) {
    if (!to_insert || !dest) {
        errno = EINVAL;
        return false;
    }
    if (to_insert->next || to_insert->prev) {
        remove_from_list(to_insert);
    }
    if (dest->prev) {
        to_insert->prev = dest->prev;
        dest->prev->next = to_insert;
    }
    dest->prev = to_insert;
    to_insert->next = dest;
    return true;
}

void node_swap(node_t* a, node_t* b) {
    if (!a || !b || a == b) {
        errno = EINVAL;
        return;
    }
    bool reverse = a->prev == b;
    if (reverse) {
        node_t* b_prev = b->prev;
        remove_from_list(b);
        remove_from_list(a);

        if (b_prev) {
            insert_node_after(a, b_prev);
        }
        insert_node_after(b, a);
    } else {
        node_t* a_prev = a->prev;
        remove_from_list(a);

        node_t* b_prev = b->prev;
        remove_from_list(b);

        if (b_prev) {
            insert_node_after(a, b_prev);
        }
        if (a_prev) {
            insert_node_after(b, a_prev);
        }
    }
}
