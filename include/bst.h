/**
 * Binary search tree header
 */

#ifndef BST_H
#define BST_H

/**
 * @brief A function pointer to a user defined function for freeing data stored
 *        in the binary search tree.
 */
typedef void (*free_f)(void *);

/**
 * @brief A function pointer to a user defined function for comparing/sorting
 *        the data in the binary search tree.
 */
typedef int (*comp_f)(const void *, const void *);

/**
 * @brief A function pointer to a user defined function for printing the data
 *        stored in the binary search tree.
 */
typedef void (*print_f)(void *);

typedef struct bst bst_t;

/**
 * @brief creates a binary search tree
 *
 * @param p_comp a pointer to a comparison function
 * @param p_free a pointer to a freeing function
 *
 * @return a pointer to a binary search tree, else NULL
 */
bst_t * bst_create(comp_f p_comp, free_f p_free);

/**
 * @brief destroys a binary search tree
 *
 * @param pp_bst the address of the binary search tree to be destroyed
 */
void bst_destroy(bst_t ** pp_bst);

/**
 * @brief inserts data into a binary search tree
 *
 * @param p_bst a pointer to a binary search tree
 * @param p_data a pointer to data to be added to the binary search tree
 *
 * @return 0 on success, else 1
 */
int bst_insert(bst_t * p_bst, void * p_data);

/**
 * @brief removes data from a binary search tree
 *
 * @param p_bst a pointer to a binary search tree
 * @param p_data a pointer to data to be removed from the binary search tree
 *
 * @return a pointer to the removed data, else NULL
 */
void * bst_remove(bst_t * p_bst, void * p_data);

/**
 * @brief prints data in a binary search tree in order
 *
 * @param p_bst a pointer to a binary search tree
 * @param p_print a pointer to a print function
 */
void bst_inorder_print(bst_t * p_bst, print_f p_print);

/**
 * @brief checks if data is in a binary search tree
 *
 * @param p_bst a pointer to a binary search tree
 * @param p_data a pointer to data to be search for in the binary search tree
 *
 * @return 0 if found, else 1
 */
int bst_search(bst_t * p_bst, void * p_data);

/**
 * @brief gets the size of a binary search tree
 *
 * @param p_bst a pointer to a binary search tree
 *
 * @return an integer for the size, 0 if pointer is NULL
 */
int bst_size(bst_t * p_bst);

#endif

// end of bst.h
