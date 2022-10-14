#ifndef CLIB_TEST_FT_LIST_H
#define CLIB_TEST_FT_LIST_H

#include <stdbool.h>
#include <stddef.h>

// TODO: write documentation

#define DATA void

/***** ft_node.c *****/

typedef struct node_s {
    struct node_s* next;
    struct node_s* prev;
    DATA* data;
} node_t;

node_t* new_node(DATA* data);
void remove_from_list(node_t* node);
void delete_node(node_t* node, void (* deleter)(DATA*));
bool insert_node_after(node_t* to_insert, node_t* dest);
bool insert_node_before(node_t* to_insert, node_t* dest);
bool node_swap(node_t* a, node_t* b);

/***** ft_list.c *****/

typedef struct list_s {
    node_t* sentinel;
    size_t size;
    void (* node_deleter)(DATA*);
} list_t;

list_t* new_list(void (* node_deteler)(DATA*));
void list_for_each(list_t* list, void (* func)(DATA*));
void list_clear(list_t* list);
void list_delete(list_t* list);
void list_push_back(list_t* list, node_t* node);
void list_push_front(list_t* list, node_t* node);
node_t* list_pop_back(list_t* list);
node_t* list_pop_front(list_t* list);
bool list_insert_at(list_t* list, node_t* node, size_t index);
node_t* list_at(list_t* list, size_t index); // const
node_t* list_begin(list_t* list); // const
node_t* list_end(list_t* list); // const
void list_append(list_t* to_append, list_t* dst);

#endif
