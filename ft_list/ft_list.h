#ifndef CLIB_TEST_FT_LIST_H
#define CLIB_TEST_FT_LIST_H

#include <stdbool.h>
#include <stddef.h>

#define DATA void

/***** ft_node.c *****/

typedef struct node_s {
    struct node_s* next;
    struct node_s* prev;
    DATA* data;
} node_t;

/**
 * allocates a new node
 * @param data data to be contained in node
 * @return newly allocated node
 */
node_t* new_node(DATA* data);

/**
 * safely remove the node from any list it might be in and relink the list
 * @param node node to be removed from list
 */
void remove_from_list(node_t* node);

/**
 * delete a node
 * @param node node to be deleted
 * @param deleter function to delete data type
 */
void delete_node(node_t* node, void (* deleter)(DATA*));

/**
 * link a node behind another node
 * @param to_insert node to be linked
 * @param dest node (potentially already part of a list) after which the other node is inserted
 * @return if the insertion was successful or not
 */
bool insert_node_after(node_t* to_insert, node_t* dest);

/**
 * link a node before another node
 * @param to_insert node to be linked
 * @param dest node (potentially already part of a list) before which the other node is inserted
 * @return if the insertion was successul or not
 */
bool insert_node_before(node_t* to_insert, node_t* dest);

/**
 * swap two nodes, including their respective places in their lists
 * @param a node to be swapped with node b
 * @param b node to be swapped with node a
 */
void node_swap(node_t* a, node_t* b);

/***** ft_list.c *****/

typedef struct list_s {
    node_t* sentinel;
    size_t size;
    void (* node_deleter)(DATA*);
} list_t;

/**
 * allocates a new list
 * @param node_deteler function that deletes DATA type in node
 * @return newly allocated list
 */
list_t* new_list(void (* node_deteler)(DATA*));

/**
 * iterate on each DATA element in a list
 * @param list allocated list to be iterated on
 * @param func function to be applied on each DATA pointer of each node in the list
 */
void list_for_each(list_t* list, void (* func)(DATA*));

/**
 * delete every node from a list, but keep the list itsself
 * @param list allocated list to be cleared
 */
void list_clear(list_t* list);

/**
 * delete and deallocate a list
 * @param list allocated list to be deleted
 */
void list_delete(list_t* list);

/**
 * add node to end of a list
 * @param list allocated list in which node is inserted
 * @param node allocated node to be added
 */
void list_push_back(list_t* list, node_t* node);

/**
 * add node to beginning of a list
 * @param list allocated list in which node is inserted
 * @param node allocated node to be added
 */
void list_push_front(list_t* list, node_t* node);

/**
 * remove and return the last element of a list
 * @param list non-empty list out of which the node is taken
 * @return the removed element
 */
node_t* list_pop_back(list_t* list);

/**
 * remove and return the first element of a list
 * @param list non-empty list out of which the node is taken
 * @return the removed element
 */
node_t* list_pop_front(list_t* list);

/**
 * insert a node at a specific index in the list
 * @param list non-empty list of at least "index" size in which the node is inserted
 * @param node allocated node to be added
 * @param index index at which the node is to be inserted
 * @return if the insertion was successful or not
 */
bool list_insert_at(list_t* list, node_t* node, size_t index);

/**
 * return the elemement at the given index
 * @param list non-empty list of at least "index" size where the element is to be found
 * @param index index at which the element is to be found
 * @return the element at index
 */
node_t* list_at(list_t* list, size_t index); // const

/**
 * return the first element of a list
 * @param list non-empty list containing desired element
 * @return the first element of the list
 */
node_t* list_begin(list_t* list); // const

/**
 * return the last element of a list
 * @param list non-empty list containing desired element
 * @return the last element of the list
 */
node_t* list_end(list_t* list); // const

/**
 * apend the elements in one list to another and then remove the source list
 * @param to_append allocated list to be appended to dst, will be deleted if any move is performed
 * @param dst allocated list at the end of which the other list is to be appended
 */
void list_append(list_t* to_append, list_t* dst);

#endif
