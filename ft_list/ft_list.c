#include <stdlib.h>
#include "ft_list.h"

list_t* new_list(void (* node_deleter)(DATA*)) {
    list_t* ret = malloc(sizeof(list_t));
    if (!ret) {
        return ret;
    }
    ret->sentinel = new_node(NULL);
    ret->sentinel->next = ret->sentinel->prev = ret->sentinel;
    ret->size = 0;
    ret->node_deleter = node_deleter;
    return ret;
}

void list_for_each(list_t* list, void (* func)(DATA*)) {
    node_t* elem = list->sentinel->next;
    while (elem != list->sentinel) {
        node_t* tmp = elem->next;
        func(elem->data);
        elem = tmp;
    }
}

void list_clear(list_t* list) {
    node_t* elem = list->sentinel->next;
    while (elem != list->sentinel) {
        node_t* tmp = elem->next;
        delete_node(elem, list->node_deleter);
        elem = tmp;
    }
    list->size = 0;
}

void list_delete(list_t* list) {
    list_clear(list);
    delete_node(list->sentinel, list->node_deleter);
    free(list);
}

void list_push_back(list_t* list, node_t* node) {
    if (insert_node_before(node, list->sentinel)) {
        ++list->size;
    }
}

void list_push_front(list_t* list, node_t* node) {
    if (insert_node_after(node, list->sentinel)) {
        ++list->size;
    }
}

node_t* list_pop_back(list_t* list) {
    if (!list->size) {
        return NULL;
    }
    node_t* elem = list->sentinel->prev;
    remove_from_list(elem);
    --list->size;
    return elem;
}

node_t* list_pop_front(list_t* list) {
    if (!list->size) {
        return NULL;
    }
    node_t* elem = list->sentinel->next;
    remove_from_list(elem);
    --list->size;
    return elem;
}

bool list_insert_at(list_t* list, node_t* node, size_t index) {
    if (index > list->size) {
        return false;
    }
    node_t* elem = list->sentinel;
    if (!list->size || index < list->size / 2) {
        while (index) {
            elem = elem->next;
            --index;
        }
        if (insert_node_after(node, elem)) {
            ++list->size;
            return true;
        }
        return false;
    } else {
        while (index != list->size) {
            elem = elem->prev;
            ++index;
        }
        if (insert_node_before(node, elem)) {
            ++list->size;
            return true;
        }
        return false;
    }
}

node_t* list_at(list_t* list, size_t index) {
    if (index >= list->size) {
        return NULL;
    }
    node_t* elem = list->sentinel;
    if (index < list->size / 2) {
        while (index) {
            elem = elem->next;
            --index;
        }
        return elem;
    } else {
        while (index != list->size) {
            elem = elem->prev;
            ++index;
        }
        return elem;
    }
}

node_t* list_begin(list_t* list) {
    if (!list->size) {
        return NULL;
    }
    return list->sentinel->next;
}

node_t* list_end(list_t* list) {
    if (!list->size) {
        return NULL;
    }
    return list->sentinel->prev;
}

void list_append(list_t* to_append, list_t* dst) {
    node_t* elem = to_append->sentinel->next;
    while (elem != to_append->sentinel) {
        node_t* tmp = elem->next;
        list_push_back(dst, elem);
        elem = tmp;
    }
    list_delete(to_append);
}