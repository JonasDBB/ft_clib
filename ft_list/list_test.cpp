#include <gtest/gtest.h>
extern "C" {
#include "ft_list.h"
}

void print_nr(void* nr) {
    printf("|%d|", *(int*)nr);
}

void print_str(void* str) {
    printf("|%s|", (char*)str);
}

TEST(node, new_node) {
    int x = 5;

    node_t* node = new_node(&x);
    ASSERT_EQ(*(int*)node->data, 5);
    free(node);
}

TEST(node, remove_from_list) {
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
}

struct my_struct {
    int* a;
    int* b;
};

void struct_freeer(void* asdf) {
    free(((struct my_struct*)asdf)->a);
    free(((struct my_struct*)asdf)->b);
}

TEST(node, delete_node) {
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
}

TEST(node, insert_node_before) {
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
    delete_node(node_x, nullptr);
    delete_node(node_y, nullptr);
    delete_node(node_z, nullptr);
}

TEST(node, insert_node_after) {
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
    delete_node(node_x, nullptr);
    delete_node(node_y, nullptr);
    delete_node(node_z, nullptr);
}

class ft_test_setup : public ::testing::Test {
protected:

    void SetUp() override {
        std::cerr << "setup.." << std::endl;
    }

    void TearDown() override {
        std::cerr << "teardown.." << std::endl;
    }
};
