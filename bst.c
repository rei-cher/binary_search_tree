/**
 * Binary search tree database.
 * Duplicate data should be rejected.
 * The tree does not own any of the data passed to it.
 * The comparison function is mandatory at creation.
 * The free function is not mandatory at creation.
 * The print function is mandatory only if and when you want to print.
 * (You will want to be able to print.)
 */

#include <stdio.h>
#include <stdlib.h>

#include "bst.h"

// struct that holds node data and children pointers
typedef struct node
{
    void *        p_data;  // pointer to saved data
    struct node * p_left;  // pointer to left child
    struct node * p_right; // pointer to right child
} node_t;

// struct that holds all binary search tree elements
struct bst
{
    node_t * p_root; // pointer to root node
    comp_f   p_comp; // pointer to user defined compare function
    free_f   p_free; // pointer to user defined free function
    int      size;   // number of nodes in the binary search tree
};

// TODO: static function prototypes here

bst_t * bst_create(comp_f p_comp, free_f p_free)
{
    (void)p_comp;
    (void)p_free;
    return NULL;
}

void bst_destroy(bst_t ** pp_bst)
{
    (void)pp_bst;
}

int bst_insert(bst_t * p_bst, void * p_data)
{
    (void)p_bst;
    (void)p_data;
    return EXIT_FAILURE;
}

void * bst_remove(bst_t * p_bst, void * p_data)
{
    (void)p_bst;
    (void)p_data;
    return NULL;
}

void bst_inorder_print(bst_t * p_bst, print_f p_print)
{
    (void)p_bst;
    (void)p_print;
}

int bst_search(bst_t * p_bst, void * p_data)
{
    (void)p_bst;
    (void)p_data;
    return EXIT_FAILURE;
}

int bst_size(bst_t * p_bst)
{
    (void)p_bst;
    return EXIT_FAILURE;
}

// TODO: static function definitions here

// end of bst.c
