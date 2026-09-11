/**
 * Binary search tree test suite
 */

#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bst.h"

static char p_buff[512] = { 0 };
static int  print_idx   = 0;

int my_int_compare(const void * a, const void * b)
{
    int x = *(const int *)a;
    int y = *(const int *)b;
    return (x > y) - (x < y);
}

void my_print(void * data)
{
    print_idx += snprintf(
        p_buff + print_idx, sizeof(p_buff) - print_idx, "%d -> ", *(int *)data);
}

void my_assert_string(const char * p_expected, const char * p_actual)
{
    if (strcmp(p_expected, p_actual) != 0)
    {
        fprintf(stderr,
                "\n  Expected: \"%s\"\n  Got:      \"%s\"\n",
                p_expected,
                p_actual);
    }

    CU_ASSERT_STRING_EQUAL(p_expected, p_actual);

    memset(p_buff, 0, sizeof(p_buff));
    print_idx = 0;
}

void test_create_destroy_empty()
{
    bst_t * p_bst = bst_create(my_int_compare, NULL);
    CU_ASSERT_PTR_NOT_NULL(p_bst);
    bst_destroy(&p_bst);
    CU_ASSERT_PTR_NULL(p_bst);

    bst_t * p_bst2 = bst_create(my_int_compare, free);
    CU_ASSERT_PTR_NOT_NULL(p_bst2);
    bst_destroy(&p_bst2);
    CU_ASSERT_PTR_NULL(p_bst2);

    bst_t * p_bst3 = bst_create(NULL, free);
    CU_ASSERT_PTR_NULL(p_bst3);
    bst_destroy(&p_bst3);

    bst_t * p_bst4 = bst_create(NULL, NULL);
    CU_ASSERT_PTR_NULL(p_bst4);
}

void test_insert_remove_stack()
{
    bst_t * p_bst   = bst_create(my_int_compare, NULL);
    int     myint1  = 1;
    int     myint2  = 2;
    int     myint3  = 3;
    int     myint6  = 6;
    int     myintn1 = -1;
    int     myint0  = 0;

    CU_ASSERT_EQUAL(EXIT_FAILURE, bst_insert(NULL, &myint1));
    CU_ASSERT_EQUAL(EXIT_FAILURE, bst_insert(p_bst, NULL));

    CU_ASSERT_EQUAL(EXIT_SUCCESS, bst_insert(p_bst, &myint1));
    CU_ASSERT_EQUAL(EXIT_SUCCESS, bst_insert(p_bst, &myint3));
    CU_ASSERT_EQUAL(EXIT_SUCCESS, bst_insert(p_bst, &myint2));
    CU_ASSERT_EQUAL(EXIT_SUCCESS, bst_insert(p_bst, &myint6));
    CU_ASSERT_EQUAL(EXIT_SUCCESS, bst_insert(p_bst, &myintn1));

    CU_ASSERT_PTR_NOT_NULL(bst_remove(p_bst, &myint1));
    CU_ASSERT_PTR_NOT_NULL(bst_remove(p_bst, &myint3));
    CU_ASSERT_PTR_NOT_NULL(bst_remove(p_bst, &myint2));
    CU_ASSERT_PTR_NOT_NULL(bst_remove(p_bst, &myint6));
    CU_ASSERT_PTR_NOT_NULL(bst_remove(p_bst, &myintn1));

    CU_ASSERT_PTR_NULL(bst_remove(p_bst, &myint1));
    CU_ASSERT_PTR_NULL(bst_remove(p_bst, &myint3));
    CU_ASSERT_PTR_NULL(bst_remove(p_bst, &myint2));
    CU_ASSERT_PTR_NULL(bst_remove(p_bst, &myint6));
    CU_ASSERT_PTR_NULL(bst_remove(p_bst, &myintn1));

    CU_ASSERT_EQUAL(EXIT_SUCCESS, bst_insert(p_bst, &myint1));
    CU_ASSERT_EQUAL(EXIT_FAILURE, bst_insert(p_bst, &myint1));

    CU_ASSERT_EQUAL(EXIT_SUCCESS, bst_insert(p_bst, &myint0));
    CU_ASSERT_EQUAL(EXIT_FAILURE, bst_insert(p_bst, &myint0));

    CU_ASSERT_EQUAL(EXIT_SUCCESS, bst_insert(p_bst, &myintn1));
    CU_ASSERT_EQUAL(EXIT_FAILURE, bst_insert(p_bst, &myintn1));

    bst_remove(p_bst, &myintn1);
    bst_remove(p_bst, &myint0);
    bst_remove(p_bst, &myint1);

    bst_destroy(&p_bst);
}

void test_insert_remove_heap()
{
    bst_t * p_bst   = bst_create(my_int_compare, NULL);
    int     myint1  = 1;
    int     myint2  = 2;
    int     myint3  = 3;
    int     myint6  = 6;
    int     myintn1 = -1;
    int     myint0  = 0;

    int * p_int1  = calloc(1, sizeof(int));
    int * p_int2  = calloc(1, sizeof(int));
    int * p_int3  = calloc(1, sizeof(int));
    int * p_int6  = calloc(1, sizeof(int));
    int * p_intn1 = calloc(1, sizeof(int));
    int * p_int0  = calloc(1, sizeof(int));

    *p_int1  = myint1;
    *p_int2  = myint2;
    *p_int3  = myint3;
    *p_int6  = myint6;
    *p_intn1 = myintn1;
    *p_int0  = myint0;

    CU_ASSERT_EQUAL(EXIT_FAILURE, bst_insert(NULL, p_int1));
    CU_ASSERT_EQUAL(EXIT_FAILURE, bst_insert(p_bst, NULL));

    CU_ASSERT_EQUAL(EXIT_SUCCESS, bst_insert(p_bst, p_int1));
    CU_ASSERT_EQUAL(EXIT_SUCCESS, bst_insert(p_bst, p_int3));
    CU_ASSERT_EQUAL(EXIT_SUCCESS, bst_insert(p_bst, p_int2));
    CU_ASSERT_EQUAL(EXIT_SUCCESS, bst_insert(p_bst, p_int6));
    CU_ASSERT_EQUAL(EXIT_SUCCESS, bst_insert(p_bst, p_intn1));

    CU_ASSERT_PTR_NOT_NULL(bst_remove(p_bst, p_int1));
    CU_ASSERT_PTR_NOT_NULL(bst_remove(p_bst, p_int3));
    CU_ASSERT_PTR_NOT_NULL(bst_remove(p_bst, p_int2));
    CU_ASSERT_PTR_NOT_NULL(bst_remove(p_bst, p_int6));
    CU_ASSERT_PTR_NOT_NULL(bst_remove(p_bst, p_intn1));

    CU_ASSERT_PTR_NULL(bst_remove(p_bst, p_int1));
    CU_ASSERT_PTR_NULL(bst_remove(p_bst, p_int3));
    CU_ASSERT_PTR_NULL(bst_remove(p_bst, p_int2));
    CU_ASSERT_PTR_NULL(bst_remove(p_bst, p_int6));
    CU_ASSERT_PTR_NULL(bst_remove(p_bst, p_intn1));

    CU_ASSERT_EQUAL(EXIT_SUCCESS, bst_insert(p_bst, p_int1));
    CU_ASSERT_EQUAL(EXIT_FAILURE, bst_insert(p_bst, p_int1));

    CU_ASSERT_EQUAL(EXIT_SUCCESS, bst_insert(p_bst, p_int0));
    CU_ASSERT_EQUAL(EXIT_FAILURE, bst_insert(p_bst, p_int0));

    CU_ASSERT_EQUAL(EXIT_SUCCESS, bst_insert(p_bst, p_intn1));
    CU_ASSERT_EQUAL(EXIT_FAILURE, bst_insert(p_bst, p_intn1));

    bst_remove(p_bst, p_intn1);
    bst_remove(p_bst, p_int0);
    bst_remove(p_bst, p_int1);

    free(p_int1);
    free(p_int2);
    free(p_int3);
    free(p_int6);
    free(p_intn1);
    free(p_int0);

    bst_destroy(&p_bst);
}

void test_destroy_nonempty()
{
    int myint1  = 1;
    int myint2  = 2;
    int myint3  = 3;
    int myint6  = 6;
    int myintn1 = -1;
    int myint0  = 0;

    int * p_int1  = calloc(1, sizeof(int));
    int * p_int2  = calloc(1, sizeof(int));
    int * p_int3  = calloc(1, sizeof(int));
    int * p_int6  = calloc(1, sizeof(int));
    int * p_intn1 = calloc(1, sizeof(int));
    int * p_int0  = calloc(1, sizeof(int));

    *p_int1  = myint1;
    *p_int2  = myint2;
    *p_int3  = myint3;
    *p_int6  = myint6;
    *p_intn1 = myintn1;
    *p_int0  = myint0;

    bst_t * p_bst = bst_create(my_int_compare, NULL);
    bst_insert(p_bst, &myint1);
    bst_insert(p_bst, &myint2);
    bst_insert(p_bst, &myint3);
    bst_insert(p_bst, &myint6);
    bst_insert(p_bst, &myintn1);
    bst_insert(p_bst, &myint0);
    bst_destroy(&p_bst);
    CU_ASSERT_PTR_NULL(p_bst);

    bst_t * p_bst2 = bst_create(my_int_compare, free);
    bst_insert(p_bst2, p_int1);
    bst_insert(p_bst2, p_int2);
    bst_insert(p_bst2, p_int3);
    bst_insert(p_bst2, p_int6);
    bst_insert(p_bst2, p_intn1);
    bst_insert(p_bst2, p_int0);
    bst_destroy(&p_bst2);
    CU_ASSERT_PTR_NULL(p_bst2);
}

void test_search_stack()
{
    bst_t * p_bst   = bst_create(my_int_compare, NULL);
    int     myint1  = 1;
    int     myint2  = 2;
    int     myint3  = 3;
    int     myint6  = 6;
    int     myintn1 = -1;

    int otherint7  = 7;
    int otherint8  = 8;
    int otherintn2 = -2;

    bst_insert(p_bst, &myint1);
    bst_insert(p_bst, &myint3);
    bst_insert(p_bst, &myint2);
    bst_insert(p_bst, &myint6);
    bst_insert(p_bst, &myintn1);

    CU_ASSERT_EQUAL(EXIT_FAILURE, bst_search(NULL, &myint1));

    CU_ASSERT_EQUAL(EXIT_SUCCESS, bst_search(p_bst, &myint1));
    CU_ASSERT_EQUAL(EXIT_SUCCESS, bst_search(p_bst, &myint3));
    CU_ASSERT_EQUAL(EXIT_SUCCESS, bst_search(p_bst, &myint2));
    CU_ASSERT_EQUAL(EXIT_SUCCESS, bst_search(p_bst, &myint6));
    CU_ASSERT_EQUAL(EXIT_SUCCESS, bst_search(p_bst, &myintn1));

    CU_ASSERT_EQUAL(EXIT_FAILURE, bst_search(p_bst, &otherint7));
    CU_ASSERT_EQUAL(EXIT_FAILURE, bst_search(p_bst, &otherint8));
    CU_ASSERT_EQUAL(EXIT_FAILURE, bst_search(p_bst, &otherintn2));

    bst_destroy(&p_bst);
}

void test_search_heap()
{
    bst_t * p_bst   = bst_create(my_int_compare, free);
    int     myint1  = 1;
    int     myint2  = 2;
    int     myint3  = 3;
    int     myint6  = 6;
    int     myintn1 = -1;

    int * p_int1  = calloc(1, sizeof(int));
    int * p_int2  = calloc(1, sizeof(int));
    int * p_int3  = calloc(1, sizeof(int));
    int * p_int6  = calloc(1, sizeof(int));
    int * p_intn1 = calloc(1, sizeof(int));

    *p_int1  = myint1;
    *p_int2  = myint2;
    *p_int3  = myint3;
    *p_int6  = myint6;
    *p_intn1 = myintn1;

    int otherint7  = 7;
    int otherint8  = 8;
    int otherintn2 = -2;

    bst_insert(p_bst, p_int1);
    bst_insert(p_bst, p_int3);
    bst_insert(p_bst, p_int2);
    bst_insert(p_bst, p_int6);
    bst_insert(p_bst, p_intn1);

    CU_ASSERT_EQUAL(EXIT_FAILURE, bst_search(NULL, p_int1));

    CU_ASSERT_EQUAL(EXIT_SUCCESS, bst_search(p_bst, p_int1));
    CU_ASSERT_EQUAL(EXIT_SUCCESS, bst_search(p_bst, p_int3));
    CU_ASSERT_EQUAL(EXIT_SUCCESS, bst_search(p_bst, p_int2));
    CU_ASSERT_EQUAL(EXIT_SUCCESS, bst_search(p_bst, p_int6));
    CU_ASSERT_EQUAL(EXIT_SUCCESS, bst_search(p_bst, p_intn1));

    CU_ASSERT_EQUAL(EXIT_FAILURE, bst_search(p_bst, &otherint7));
    CU_ASSERT_EQUAL(EXIT_FAILURE, bst_search(p_bst, &otherint8));
    CU_ASSERT_EQUAL(EXIT_FAILURE, bst_search(p_bst, &otherintn2));

    bst_destroy(&p_bst);
}

void test_size()
{
    bst_t * p_bst   = bst_create(my_int_compare, NULL);
    int     myint1  = 1;
    int     myint2  = 2;
    int     myint3  = 3;
    int     myint6  = 6;
    int     myintn1 = -1;

    CU_ASSERT_EQUAL(0, bst_size(NULL));
    CU_ASSERT_EQUAL(0, bst_size(p_bst));

    bst_insert(p_bst, &myint1);
    CU_ASSERT_EQUAL(1, bst_size(p_bst));

    bst_insert(p_bst, &myint3);
    CU_ASSERT_EQUAL(2, bst_size(p_bst));

    bst_insert(p_bst, &myint2);
    CU_ASSERT_EQUAL(3, bst_size(p_bst));

    bst_insert(p_bst, &myint6);
    CU_ASSERT_EQUAL(4, bst_size(p_bst));

    bst_insert(p_bst, &myintn1);
    CU_ASSERT_EQUAL(5, bst_size(p_bst));

    bst_remove(p_bst, &myintn1);
    CU_ASSERT_EQUAL(4, bst_size(p_bst));

    bst_insert(p_bst, &myintn1);
    CU_ASSERT_EQUAL(5, bst_size(p_bst));

    bst_remove(p_bst, &myintn1);
    CU_ASSERT_EQUAL(4, bst_size(p_bst));

    bst_remove(p_bst, &myint6);
    CU_ASSERT_EQUAL(3, bst_size(p_bst));

    bst_remove(p_bst, &myint3);
    CU_ASSERT_EQUAL(2, bst_size(p_bst));

    bst_remove(p_bst, &myint1);
    CU_ASSERT_EQUAL(1, bst_size(p_bst));

    bst_remove(p_bst, &myint2);
    CU_ASSERT_EQUAL(0, bst_size(p_bst));

    bst_destroy(&p_bst);
}

void test_inorder_simple()
{
    bst_t * p_bst = bst_create(my_int_compare, NULL);

    int myint2 = 2;
    int myint3 = 3;
    int myint4 = 4;
    int myint5 = 5;
    int myint6 = 6;
    int myint7 = 7;
    int myint8 = 8;

    bst_insert(p_bst, &myint5);
    bst_insert(p_bst, &myint3);
    bst_insert(p_bst, &myint7);
    bst_insert(p_bst, &myint2);
    bst_insert(p_bst, &myint4);
    bst_insert(p_bst, &myint6);
    bst_insert(p_bst, &myint8);

    bst_inorder_print(p_bst, my_print);

    my_assert_string("2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8 -> ", p_buff);

    bst_destroy(&p_bst);
}

void test_always_left()
{
    bst_t * p_bst = bst_create(my_int_compare, NULL);

    int myint2 = 2;
    int myint3 = 3;
    int myint4 = 4;
    int myint5 = 5;
    int myint6 = 6;
    int myint7 = 7;
    int myint8 = 8;

    bst_insert(p_bst, &myint8);
    bst_insert(p_bst, &myint7);
    bst_insert(p_bst, &myint6);
    bst_insert(p_bst, &myint5);
    bst_insert(p_bst, &myint4);
    bst_insert(p_bst, &myint3);
    bst_insert(p_bst, &myint2);

    bst_inorder_print(p_bst, my_print);

    my_assert_string("2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8 -> ", p_buff);

    bst_destroy(&p_bst);
}

void test_always_right()
{
    bst_t * p_bst = bst_create(my_int_compare, NULL);

    int myint2 = 2;
    int myint3 = 3;
    int myint4 = 4;
    int myint5 = 5;
    int myint6 = 6;
    int myint7 = 7;
    int myint8 = 8;

    bst_insert(p_bst, &myint2);
    bst_insert(p_bst, &myint3);
    bst_insert(p_bst, &myint4);
    bst_insert(p_bst, &myint5);
    bst_insert(p_bst, &myint6);
    bst_insert(p_bst, &myint7);
    bst_insert(p_bst, &myint8);

    bst_inorder_print(p_bst, my_print);

    my_assert_string("2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8 -> ", p_buff);

    bst_destroy(&p_bst);
}

void test_random()
{
    bst_t * p_bst = bst_create(my_int_compare, NULL);

    int myint2 = 2;
    int myint3 = 3;
    int myint4 = 4;
    int myint5 = 5;
    int myint6 = 6;
    int myint7 = 7;
    int myint8 = 8;

    bst_insert(p_bst, &myint5);
    bst_insert(p_bst, &myint4);
    bst_insert(p_bst, &myint2);
    bst_insert(p_bst, &myint3);
    bst_insert(p_bst, &myint8);
    bst_insert(p_bst, &myint6);
    bst_insert(p_bst, &myint7);

    bst_inorder_print(p_bst, my_print);

    my_assert_string("2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8 -> ", p_buff);

    bst_destroy(&p_bst);
}

void test_remove_simple()
{
    bst_t * p_bst = bst_create(my_int_compare, NULL);

    int myint2 = 2;
    int myint3 = 3;
    int myint4 = 4;
    int myint5 = 5;
    int myint6 = 6;
    int myint7 = 7;
    int myint8 = 8;

    bst_insert(p_bst, &myint5);
    bst_insert(p_bst, &myint3);
    bst_insert(p_bst, &myint7);
    bst_insert(p_bst, &myint2);
    bst_insert(p_bst, &myint4);
    bst_insert(p_bst, &myint6);
    bst_insert(p_bst, &myint8);

    bst_remove(p_bst, &myint8);
    bst_inorder_print(p_bst, my_print);
    my_assert_string("2 -> 3 -> 4 -> 5 -> 6 -> 7 -> ", p_buff);

    bst_remove(p_bst, &myint6);
    bst_inorder_print(p_bst, my_print);
    my_assert_string("2 -> 3 -> 4 -> 5 -> 7 -> ", p_buff);

    bst_remove(p_bst, &myint4);
    bst_inorder_print(p_bst, my_print);
    my_assert_string("2 -> 3 -> 5 -> 7 -> ", p_buff);

    bst_remove(p_bst, &myint2);
    bst_inorder_print(p_bst, my_print);
    my_assert_string("3 -> 5 -> 7 -> ", p_buff);

    bst_remove(p_bst, &myint7);
    bst_inorder_print(p_bst, my_print);
    my_assert_string("3 -> 5 -> ", p_buff);

    bst_remove(p_bst, &myint3);
    bst_inorder_print(p_bst, my_print);
    my_assert_string("5 -> ", p_buff);

    bst_remove(p_bst, &myint5);
    bst_inorder_print(p_bst, my_print);
    my_assert_string("", p_buff);

    bst_destroy(&p_bst);
}

void test_remove_root_min_right()
{
    bst_t * p_bst = bst_create(my_int_compare, NULL);

    int myint2 = 2;
    int myint3 = 3;
    int myint4 = 4;
    int myint5 = 5;
    int myint6 = 6;
    int myint7 = 7;
    int myint8 = 8;

    bst_insert(p_bst, &myint5);
    bst_insert(p_bst, &myint3);
    bst_insert(p_bst, &myint7);
    bst_insert(p_bst, &myint2);
    bst_insert(p_bst, &myint4);
    bst_insert(p_bst, &myint6);
    bst_insert(p_bst, &myint8);

    bst_remove(p_bst, &myint5);
    bst_inorder_print(p_bst, my_print);
    my_assert_string("2 -> 3 -> 4 -> 6 -> 7 -> 8 -> ", p_buff);

    bst_remove(p_bst, &myint6);
    bst_inorder_print(p_bst, my_print);
    my_assert_string("2 -> 3 -> 4 -> 7 -> 8 -> ", p_buff);

    bst_remove(p_bst, &myint7);
    bst_inorder_print(p_bst, my_print);
    my_assert_string("2 -> 3 -> 4 -> 8 -> ", p_buff);

    bst_remove(p_bst, &myint8);
    bst_inorder_print(p_bst, my_print);
    my_assert_string("2 -> 3 -> 4 -> ", p_buff);

    bst_remove(p_bst, &myint3);
    bst_inorder_print(p_bst, my_print);
    my_assert_string("2 -> 4 -> ", p_buff);

    bst_remove(p_bst, &myint4);
    bst_inorder_print(p_bst, my_print);
    my_assert_string("2 -> ", p_buff);

    bst_remove(p_bst, &myint2);
    bst_inorder_print(p_bst, my_print);
    my_assert_string("", p_buff);

    bst_destroy(&p_bst);
}

void test_remove_root_max_left()
{
    bst_t * p_bst = bst_create(my_int_compare, NULL);

    int myint2 = 2;
    int myint3 = 3;
    int myint4 = 4;
    int myint5 = 5;
    int myint6 = 6;
    int myint7 = 7;
    int myint8 = 8;

    bst_insert(p_bst, &myint5);
    bst_insert(p_bst, &myint3);
    bst_insert(p_bst, &myint7);
    bst_insert(p_bst, &myint2);
    bst_insert(p_bst, &myint4);
    bst_insert(p_bst, &myint6);
    bst_insert(p_bst, &myint8);

    bst_remove(p_bst, &myint5);
    bst_inorder_print(p_bst, my_print);
    my_assert_string("2 -> 3 -> 4 -> 6 -> 7 -> 8 -> ", p_buff);

    bst_remove(p_bst, &myint4);
    bst_inorder_print(p_bst, my_print);
    my_assert_string("2 -> 3 -> 6 -> 7 -> 8 -> ", p_buff);

    bst_remove(p_bst, &myint3);
    bst_inorder_print(p_bst, my_print);
    my_assert_string("2 -> 6 -> 7 -> 8 -> ", p_buff);

    bst_remove(p_bst, &myint2);
    bst_inorder_print(p_bst, my_print);
    my_assert_string("6 -> 7 -> 8 -> ", p_buff);

    bst_remove(p_bst, &myint7);
    bst_inorder_print(p_bst, my_print);
    my_assert_string("6 -> 8 -> ", p_buff);

    bst_remove(p_bst, &myint6);
    bst_inorder_print(p_bst, my_print);
    my_assert_string("8 -> ", p_buff);

    bst_remove(p_bst, &myint8);
    bst_inorder_print(p_bst, my_print);
    my_assert_string("", p_buff);

    bst_destroy(&p_bst);
}

int main(void)
{
    CU_TestInfo suite1_tests[] = {
        { "Testing creation and destruction:", test_create_destroy_empty },
        { "Testing insertion and removal (stack):", test_insert_remove_stack },
        { "Testing insertion and removal (heap):", test_insert_remove_heap },
        { "Testing nonempty destruction:", test_destroy_nonempty },
        { "Testing search (stack):", test_search_stack },
        { "Testing search (heap):", test_search_heap },
        { "Testing size:", test_size },
        CU_TEST_INFO_NULL
    };

    CU_TestInfo suite2_tests[] = {
        { "Testing simple node arrangement:", test_inorder_simple },
        { "Testing only left node insertion:", test_always_left },
        { "Testing only right node insertion:", test_always_right },
        { "Testing random insertion:", test_random },
        { "Testing simple node removal:", test_remove_simple },
        { "Testing root node then min right removal:",
          test_remove_root_min_right },
        { "Testing root node then max left removal:",
          test_remove_root_max_left },
        CU_TEST_INFO_NULL
    };

    CU_SuiteInfo suites[] = {
        { "Suite-1:", NULL, NULL, .pTests = suite1_tests },
        { "Suite-2:", NULL, NULL, .pTests = suite2_tests },
        CU_SUITE_INFO_NULL
    };

    if (CUE_SUCCESS != CU_initialize_registry())
    {
        return CU_get_error();
    }

    if (0 != CU_register_suites(suites))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_basic_show_failures(CU_get_failure_list());
    int num_failed = CU_get_number_of_failures();
    CU_cleanup_registry();
    puts("\n");
    return num_failed;
}

// end of bst_test.c
