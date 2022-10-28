#include <gtest/gtest.h>

extern "C" {
#include "ft_list.h"
}

TEST(node, NewNode) {
    int x = 5;

    node_t* node = new_node(&x);
    ASSERT_EQ(*(int*)node->data, 5);
    free(node);
}

TEST(node, RemoveFromList) {
    int x = 1;
    int y = 2;
    int z = 3;

    node_t* node_x = new_node(&x);
    node_t* node_y = new_node(&y);
    node_t* node_z = new_node(&z);

    node_x->next = node_y;
    node_y->prev = node_x;
    node_y->next = node_z;
    node_z->prev = node_y;

    remove_from_list(node_y);
    ASSERT_EQ(node_x->next, node_z);
    ASSERT_EQ(node_z->prev, node_x);
    ASSERT_EQ(node_y->next, nullptr);
    ASSERT_EQ(node_y->prev, nullptr);

    free(node_x);
    free(node_y);
    free(node_z);

    errno = 0;
    remove_from_list(nullptr);
    ASSERT_EQ(errno, EINVAL);
}

struct my_struct {
    int* a;
    int* b;
};

void struct_freeer(void* asdf) {
    free(((struct my_struct*)asdf)->a);
    free(((struct my_struct*)asdf)->b);
}

TEST(node, DeleteNode) {
    int x = 5;
    node_t* node_x = new_node(&x);

    int* y = (int*)malloc(sizeof(int));
    *y = 4;
    node_t* node_y = new_node(y);

    my_struct my_strct{};
    my_strct.a = (int*)malloc(sizeof(int));
    *my_strct.a = 3;
    my_strct.b = (int*)malloc(sizeof(int));
    *my_strct.b = 2;
    node_t* node_strct = new_node(&my_strct);

    // the test is if there is any memory leaks afterwards
    delete_node(node_x, nullptr);
    delete_node(node_y, free);
    delete_node(node_strct, struct_freeer);

    errno = 0;
    delete_node(nullptr, nullptr);
    ASSERT_EQ(errno, EINVAL);
}

TEST(node, InsertNodeBefore) {
    int x = 1;
    int y = 2;
    int z = 3;

    node_t* node_x = new_node(&x);
    node_t* node_y = new_node(&y);
    node_t* node_z = new_node(&z);

    insert_node_before(node_y, node_z);
    insert_node_before(node_x, node_y);
    ASSERT_EQ(node_x->next, node_y);
    ASSERT_EQ(node_y->next, node_z);
    ASSERT_EQ(node_z->next, nullptr);
    ASSERT_EQ(node_x->prev, nullptr);
    ASSERT_EQ(node_y->prev, node_x);
    ASSERT_EQ(node_z->prev, node_y);

    int i = 4;
    node_t* node_i = new_node(&i);
    insert_node_before(node_x, node_i);
    ASSERT_EQ(node_i->prev, node_x);
    ASSERT_EQ(node_y->prev, nullptr);
    ASSERT_EQ(node_x->prev, nullptr);
    ASSERT_EQ(node_x->next, node_i);
    insert_node_before(node_z, node_i);
    ASSERT_EQ(node_i->prev, node_z);
    ASSERT_EQ(node_y->next, nullptr);
    ASSERT_EQ(node_z->prev, node_x);
    ASSERT_EQ(node_z->next, node_i);

    errno = 0;
    insert_node_before(node_x, nullptr);
    ASSERT_EQ(errno, EINVAL);
    errno = 0;
    insert_node_before(nullptr, node_x);
    ASSERT_EQ(errno, EINVAL);

    delete_node(node_x, nullptr);
    delete_node(node_y, nullptr);
    delete_node(node_z, nullptr);
    delete_node(node_i, nullptr);

    errno = 0;
    insert_node_before(nullptr, nullptr);
    ASSERT_EQ(errno, EINVAL);
}

TEST(node, InsertNodeAfter) {
    int x = 1;
    int y = 2;
    int z = 3;

    node_t* node_x = new_node(&x);
    node_t* node_y = new_node(&y);
    node_t* node_z = new_node(&z);

    insert_node_after(node_y, node_x);
    insert_node_after(node_z, node_y);
    ASSERT_EQ(node_x->next, node_y);
    ASSERT_EQ(node_y->next, node_z);
    ASSERT_EQ(node_z->next, nullptr);
    ASSERT_EQ(node_x->prev, nullptr);
    ASSERT_EQ(node_y->prev, node_x);
    ASSERT_EQ(node_z->prev, node_y);

    int i = 4;
    node_t* node_i = new_node(&i);
    insert_node_after(node_x, node_i);
    ASSERT_EQ(node_i->next, node_x);
    ASSERT_EQ(node_y->prev, nullptr);
    ASSERT_EQ(node_x->next, nullptr);
    ASSERT_EQ(node_x->prev, node_i);
    insert_node_after(node_z, node_i);
    ASSERT_EQ(node_i->next, node_z);
    ASSERT_EQ(node_y->next, nullptr);
    ASSERT_EQ(node_z->next, node_x);
    ASSERT_EQ(node_z->prev, node_i);

    errno = 0;
    insert_node_after(node_x, nullptr);
    ASSERT_EQ(errno, EINVAL);
    errno = 0;
    insert_node_after(nullptr, node_x);
    ASSERT_EQ(errno, EINVAL);

    delete_node(node_x, nullptr);
    delete_node(node_y, nullptr);
    delete_node(node_z, nullptr);
    delete_node(node_i, nullptr);

    errno = 0;
    insert_node_after(nullptr, nullptr);
    ASSERT_EQ(errno, EINVAL);
}

TEST(node, SwapNode) {
    list_t* list1 = list_new(nullptr);
    int x = 1;
    int y = 2;
    int z = 3;
    node_t* node_1 = new_node(&x);
    node_t* node_2 = new_node(&y);
    node_t* node_3 = new_node(&z);
    list_push_back(list1, node_1);
    list_push_back(list1, node_2);
    list_push_back(list1, node_3);

    list_t* list2 = list_new(nullptr);
    int a = 4;
    int b = 5;
    int c = 6;
    node_t* node_4 = new_node(&a);
    node_t* node_5 = new_node(&b);
    node_t* node_6 = new_node(&c);
    list_push_back(list2, node_4);
    list_push_back(list2, node_5);
    list_push_back(list2, node_6);

    // 1 - 2 - 3 | 4 - 5 - 6
    ASSERT_EQ(*(int*)(list1->sentinel->next->data), 1);
    ASSERT_EQ(*(int*)(list1->sentinel->next->next->data), 2);
    ASSERT_EQ(*(int*)(list1->sentinel->next->next->next->data), 3);
    ASSERT_EQ(*(int*)(list2->sentinel->next->data), 4);
    ASSERT_EQ(*(int*)(list2->sentinel->next->next->data), 5);
    ASSERT_EQ(*(int*)(list2->sentinel->next->next->next->data), 6);

    node_swap(node_2, node_5);

    // 1 - 5 - 3 | 4 - 2 - 6
    ASSERT_EQ(*(int*)(list1->sentinel->next->data), 1);
    ASSERT_EQ(*(int*)(list1->sentinel->next->next->data), 5);
    ASSERT_EQ(*(int*)(list1->sentinel->next->next->next->data), 3);
    ASSERT_EQ(*(int*)(list2->sentinel->next->data), 4);
    ASSERT_EQ(*(int*)(list2->sentinel->next->next->data), 2);
    ASSERT_EQ(*(int*)(list2->sentinel->next->next->next->data), 6);
    // swap 1 and 5, where a->next == b
    node_swap(node_1, node_5);
    // 5 - 1 - 3 | 4 - 2 - 6
    ASSERT_EQ(*(int*)(list1->sentinel->next->data), 5);
    ASSERT_EQ(*(int*)(list1->sentinel->next->next->data), 1);
    ASSERT_EQ(*(int*)(list1->sentinel->next->next->next->data), 3);

    // swap 1 and 5, where a->prev == b
    node_swap(node_1, node_5);
    // 1 - 5 - 3 | 4 - 2 - 6
    ASSERT_EQ(*(int*)(list1->sentinel->next->data), 1);
    ASSERT_EQ(*(int*)(list1->sentinel->next->next->data), 5);
    ASSERT_EQ(*(int*)(list1->sentinel->next->next->next->data), 3);

    node_t* node_x = new_node(&x);
    node_t* node_y = new_node(&y);
//    node_t* node_z = new_node(&z);

    node_swap(node_x, node_y);
    ASSERT_EQ(node_x->next, nullptr);
    ASSERT_EQ(node_x->prev, nullptr);
    ASSERT_EQ(node_y->next, nullptr);
    ASSERT_EQ(node_y->prev, nullptr);

    insert_node_after(node_y, node_x);
    ASSERT_EQ(node_x->next, node_y);
    ASSERT_EQ(node_x->prev, nullptr);
    ASSERT_EQ(node_y->next, nullptr);
    ASSERT_EQ(node_y->prev, node_x);

    node_swap(node_y, node_x);
    ASSERT_EQ(node_x->next, nullptr);
    ASSERT_EQ(node_x->prev, node_y);
    ASSERT_EQ(node_y->next, node_x);
    ASSERT_EQ(node_y->prev, nullptr);

    errno = 0;
    node_swap(node_1, node_1);
    ASSERT_EQ(errno, EINVAL);
    errno = 0;
    node_swap(nullptr, node_1);
    ASSERT_EQ(errno, EINVAL);
    errno = 0;
    node_swap(node_1, nullptr);
    ASSERT_EQ(errno, EINVAL);

    delete_node(node_x, nullptr);
    delete_node(node_y, nullptr);
//    delete_node(node_z, nullptr);

    list_delete(list1);
    list_delete(list2);
}

class ft_test_setup : public ::testing::Test {
public:
    ft_test_setup() : _list(nullptr), _node_x(nullptr), _node_y(nullptr), _node_z(nullptr) {}

protected:
    list_t* _list;
    node_t* _node_x;
    node_t* _node_y;
    node_t* _node_z;

    void SetUp() override {
        errno = 0;
        int x = 1;
        int y = 2;
        int z = 3;

        _node_x = new_node(&x);
        _node_y = new_node(&y);
        _node_z = new_node(&z);
        _list = list_new(nullptr);
        list_push_back(_list, _node_x);
        list_push_back(_list, _node_y);
        list_push_back(_list, _node_z);
    }

    void TearDown() override {
        errno = 0;
        list_delete(_list);
    }
};

TEST(list, ListNew) {
    list_t* list = list_new(nullptr);

    ASSERT_EQ(list->size, 0);
    ASSERT_NE(list->sentinel, nullptr);
    list_delete(list);
}

TEST(list, ListDelete) {
    list_t* list = list_new(nullptr);

    // only testing if this leaks
    list_delete(list);

    list_t* list_a = list_new(struct_freeer);
    my_struct my_strct0{};
    my_strct0.a = (int*)malloc(sizeof(int));
    *my_strct0.a = 3;
    my_strct0.b = (int*)malloc(sizeof(int));
    *my_strct0.b = 2;
    node_t* node_strct0 = new_node(&my_strct0);
    my_struct my_strct1{};
    my_strct1.a = (int*)malloc(sizeof(int));
    *my_strct1.a = 3;
    my_strct1.b = (int*)malloc(sizeof(int));
    *my_strct1.b = 2;
    node_t* node_strct1 = new_node(&my_strct1);

    list_push_back(list_a, node_strct0);
    list_push_back(list_a, node_strct1);
    // only testing if this leaks
    list_delete(list_a);

    errno = 0;
    list_delete(nullptr);
    ASSERT_EQ(errno, EINVAL);
}

TEST(list, ListPushBack) {
    list_t* list = list_new(nullptr);
    int x = 1;
    int y = 2;
    int z = 3;

    node_t* node_x = new_node(&x);
    node_t* node_y = new_node(&y);
    node_t* node_z = new_node(&z);
    ASSERT_EQ(list->size, 0);
    list_push_back(list, node_x);
    list_push_back(list, node_y);
    list_push_back(list, node_z);
    ASSERT_EQ(list->size, 3);
    ASSERT_EQ(list->sentinel->next->next, node_y);
    ASSERT_EQ(list->sentinel->next->next->next, node_z);
    ASSERT_EQ(list->sentinel->next->next->next->next, list->sentinel);
    ASSERT_EQ(list->sentinel->prev, node_z);
    ASSERT_EQ(list->sentinel->prev->prev, node_y);
    ASSERT_EQ(list->sentinel->prev->prev->prev, node_x);
    ASSERT_EQ(list->sentinel->prev->prev->prev->prev, list->sentinel);
    ASSERT_EQ(list->sentinel->next, node_x);

    errno = 0;
    list_push_back(nullptr, node_x);
    ASSERT_EQ(errno, EINVAL);
    errno = 0;
    list_push_back(list, nullptr);
    ASSERT_EQ(errno, EINVAL);

    list_delete(list);
}

TEST(list, ListPushFront) {
    list_t* list = list_new(nullptr);
    int x = 1;
    int y = 2;
    int z = 3;

    node_t* node_x = new_node(&x);
    node_t* node_y = new_node(&y);
    node_t* node_z = new_node(&z);
    ASSERT_EQ(list->size, 0);
    list_push_front(list, node_z);
    list_push_front(list, node_y);
    list_push_front(list, node_x);
    ASSERT_EQ(list->size, 3);
    ASSERT_EQ(list->sentinel->next, node_x);
    ASSERT_EQ(list->sentinel->next->next, node_y);
    ASSERT_EQ(list->sentinel->next->next->next, node_z);
    ASSERT_EQ(list->sentinel->next->next->next->next, list->sentinel);
    ASSERT_EQ(list->sentinel->prev, node_z);
    ASSERT_EQ(list->sentinel->prev->prev, node_y);
    ASSERT_EQ(list->sentinel->prev->prev->prev, node_x);
    ASSERT_EQ(list->sentinel->prev->prev->prev->prev, list->sentinel);

    errno = 0;
    list_push_front(nullptr, node_x);
    ASSERT_EQ(errno, EINVAL);
    errno = 0;
    list_push_front(list, nullptr);
    ASSERT_EQ(errno, EINVAL);

    list_delete(list);
}

TEST_F(ft_test_setup, ListPopBack) {
    node_t* tmp;
    ASSERT_EQ(_list->size, 3);
    tmp = list_pop_back(_list);
    ASSERT_EQ(_list->size, 2);
    ASSERT_EQ(tmp, _node_z);
    delete_node(tmp, nullptr);

    tmp = list_pop_back(_list);
    ASSERT_EQ(_list->size, 1);
    ASSERT_EQ(tmp, _node_y);
    delete_node(tmp, nullptr);

    tmp = list_pop_back(_list);
    ASSERT_EQ(_list->size, 0);
    ASSERT_EQ(tmp, _node_x);
    delete_node(tmp, nullptr);

    tmp = list_pop_back(_list);
    ASSERT_EQ(_list->size, 0);
    ASSERT_EQ(tmp, nullptr);
    ASSERT_EQ(errno, ERANGE);

    errno = 0;
    list_pop_back(nullptr);
    ASSERT_EQ(errno, EINVAL);
}

TEST_F(ft_test_setup, ListPopFront) {
    node_t* tmp;
    ASSERT_EQ(_list->size, 3);
    tmp = list_pop_front(_list);
    ASSERT_EQ(_list->size, 2);
    ASSERT_EQ(tmp, _node_x);
    delete_node(tmp, nullptr);

    tmp = list_pop_front(_list);
    ASSERT_EQ(_list->size, 1);
    ASSERT_EQ(tmp, _node_y);
    delete_node(tmp, nullptr);

    tmp = list_pop_front(_list);
    ASSERT_EQ(_list->size, 0);
    ASSERT_EQ(tmp, _node_z);
    delete_node(tmp, nullptr);

    tmp = list_pop_front(_list);
    ASSERT_EQ(_list->size, 0);
    ASSERT_EQ(tmp, nullptr);
    ASSERT_EQ(errno, ERANGE);

    errno = 0;
    list_pop_front(nullptr);
    ASSERT_EQ(errno, EINVAL);
}

TEST_F(ft_test_setup, ListClear) {
    ASSERT_EQ(_list->size, 3);
    list_clear(_list);
    ASSERT_EQ(_list->size, 0);
    ASSERT_NE(_list->sentinel, nullptr);
    list_clear(_list);
    ASSERT_EQ(_list->size, 0);
    ASSERT_NE(_list->sentinel, nullptr);

    list_clear(nullptr);
    ASSERT_EQ(errno, EINVAL);
}

void multiply_nr(void* nr) {
    (*(char*)nr)++;
}

TEST(list, ListForEach) {
    int x = 1;
    int y = 2;
    int z = 3;

    node_t* node_x = new_node(&x);
    node_t* node_y = new_node(&y);
    node_t* node_z = new_node(&z);
    list_t* list = list_new(nullptr);
    list_push_back(list, node_x);
    list_push_back(list, node_y);
    list_push_back(list, node_z);

    list_for_each(list, multiply_nr);
    ASSERT_EQ(*(int*)(list->sentinel->next->data), 2);
    ASSERT_EQ(*(int*)(list->sentinel->next->next->data), 3);
    ASSERT_EQ(*(int*)(list->sentinel->next->next->next->data), 4);

    list_for_each(nullptr, multiply_nr);
    ASSERT_EQ(errno, EINVAL);

    errno = 0;
    list_for_each(list, nullptr);
    ASSERT_EQ(errno, EINVAL);
    list_delete(list);
}

TEST_F(ft_test_setup, ListInsertAt) {
    int a = 5;
    int b = 6;
    int c = 7;
    node_t* node_a = new_node(&a);
    node_t* node_b = new_node(&b);
    node_t* node_c = new_node(&c);

    list_insert_at(_list, node_a, 42);
    ASSERT_EQ(_list->size, 3);
    ASSERT_EQ(errno, ERANGE);
    ASSERT_EQ(node_a->prev, nullptr);
    ASSERT_EQ(node_a->next, nullptr);
    errno = 0;

    list_insert_at(_list, node_a, 1);
    ASSERT_EQ(_list->size, 4);
    ASSERT_EQ(_node_x->next, node_a);
    ASSERT_EQ(node_a->prev, _node_x);
    ASSERT_EQ(_node_y->prev, node_a);
    ASSERT_EQ(node_a->next, _node_y);

    list_insert_at(_list, node_b, 4);
    ASSERT_EQ(_list->size, 5);
    ASSERT_EQ(_node_z->next, node_b);
    ASSERT_EQ(node_b->prev, _node_z);
    ASSERT_EQ(_list->sentinel->prev, node_b);
    ASSERT_EQ(node_b->next, _list->sentinel);

    list_insert_at(_list, node_c, 6);
    ASSERT_EQ(_list->size, 5);
    ASSERT_EQ(errno, ERANGE);
    errno = 0;
    delete_node(node_c, nullptr);

    list_insert_at(nullptr, node_a, 1);
    ASSERT_EQ(errno, EINVAL);
    errno = 0;

    list_insert_at(_list, nullptr, 1);
    ASSERT_EQ(errno, EINVAL);
    errno = 0;
    list_insert_at(_list, node_a, -1);
    ASSERT_EQ(errno, ERANGE);
}

TEST_F(ft_test_setup, ListAt) {
    ASSERT_EQ(list_at(_list, 0), _node_x);
    ASSERT_EQ(list_at(_list, 1), _node_y);
    ASSERT_EQ(list_at(_list, 2), _node_z);

    ASSERT_EQ(list_at(_list, -1), nullptr);
    ASSERT_EQ(errno, ERANGE);
    errno = 0;

    ASSERT_EQ(list_at(_list, 8), nullptr);
    ASSERT_EQ(errno, ERANGE);
    errno = 0;

    ASSERT_EQ(list_at(nullptr, 1), nullptr);
    ASSERT_EQ(errno, EINVAL);
}

TEST_F(ft_test_setup, ListBegin) {
    ASSERT_EQ(list_begin(_list), _node_x);

    list_t* empty_list = list_new(nullptr);
    ASSERT_EQ(list_begin(empty_list), nullptr);
    ASSERT_EQ(errno, EINVAL);
    errno = 0;
    list_delete(empty_list);

    ASSERT_EQ(list_begin(nullptr), nullptr);
    ASSERT_EQ(errno, EINVAL);
}

TEST_F(ft_test_setup, ListEnd) {
    ASSERT_EQ(list_end(_list), _node_z);

    list_t* empty_list = list_new(nullptr);
    ASSERT_EQ(list_end(empty_list), nullptr);
    ASSERT_EQ(errno, EINVAL);
    errno = 0;
    list_delete(empty_list);

    ASSERT_EQ(list_end(nullptr), nullptr);
    ASSERT_EQ(errno, EINVAL);
}

TEST_F(ft_test_setup, ListAppend) {
    list_t* new_list = list_new(nullptr);
    int nrs[10] = {11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    for (int& nr: nrs) {
        node_t* node = new_node(&nr);
        list_push_back(new_list, node);
    }

    ASSERT_EQ(_list->size, 3);
    ASSERT_EQ(new_list->size, 10);
    list_append(new_list, _list);
    ASSERT_EQ(_list->size, 13);
    ASSERT_EQ(_list->sentinel->next, _node_x);
    ASSERT_EQ(*(int*)_list->sentinel->prev->data, 20);
    ASSERT_EQ(*(int*)_node_z->next->data, 11);
    // new_list should already be deallocated, if not it will leak

    list_append(nullptr, _list);
    ASSERT_EQ(errno, EINVAL);
    errno = 0;
    list_append(_list, nullptr);
    ASSERT_EQ(errno, EINVAL);
}
