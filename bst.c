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
static node_t * node_find(node_t * p_root, void * p_data);
static node_t * find_smallest(node_t * p_node);
static node_t * remove_node(node_t * p_node, void * p_data);
static void insert_left(node_t * p_node, void * p_data);
static void insert_right(node_t * p_node, void * p_data);

bst_t * bst_create(comp_f p_comp, free_f p_free)
{
	bst_t * new_bst = NULL;

	if (NULL == p_comp)
	{
		goto END;
	}

	new_bst = calloc(1, sizeof(bst_t));

	if (NULL == new_bst)
	{
		goto END;
	}

	new_bst->p_root = NULL;
	new_bst->p_comp = p_comp;
	new_bst->p_free = p_free;
	new_bst->size = 0;

END:
	return new_bst;
}

void bst_destroy(bst_t ** pp_bst)
{
	if ((NULL == pp_bst) ||
		(NULL == (* pp_bst)))
	{
		goto END;
	}

	if (0 != (* pp_bst)->size)
	{
		bst_remove((* pp_bst), (* pp_bst)->p_root->p_data);
	}

	free(* pp_bst);
	(* pp_bst) = NULL;

END:
	return;
}

int bst_insert(bst_t * p_bst, void * p_data)
{
	int SUCCESS = 1;

	if ((NULL == p_bst) ||
		(NULL == p_data) ||
		(NULL != node_find(p_bst->p_root, p_data)))
	{
		goto END;
	}

	if (NULL == p_bst->p_root)
	{
		p_bst->p_root->p_data = p_data;
		p_bst->p_root->p_left = NULL;
		p_bst->p_root->p_right = NULL;

		p_bst->size++;

		SUCCESS = 0;
		goto END;
	}
	
	node_t * p_tmp = NULL;
	node_t * p_current = p_bst->p_root;

	while (NULL != p_current)
	{
		if (0 < p_bst->p_comp(p_current->p_data, p_data))
		{
			p_tmp = p_current;
			p_current = p_current->p_left;
		}

		if (0 > p_bst->p_comp(p_current->p_data, p_data))
		{
			p_tmp = p_current;
			p_current = p_current->p_right;
		}
	}

	if (p_tmp->p_data > p_data)
	{
		insert_left(p_tmp, p_data);
	}
	else
	{
		insert_right(p_tmp, p_data);
	}
	
	p_bst->size++;

	SUCCESS = 0;
	
END:
	return SUCCESS;
}

void * bst_remove(bst_t * p_bst, void * p_data)
{
	node_t * p_removed = NULL;

	if ((NULL == p_bst) ||
		(NULL == p_data) ||
		(NULL == p_bst->p_root))
	{
		goto END;
	}

	p_removed = remove_node(p_bst->p_root, p_data);

END:
	return p_removed;
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
static node_t * remove_node(node_t * p_node, void * p_data)
{
	node_t * p_removed = NULL;

	if ((NULL == p_node) ||
		(NULL == p_data))
	{
		goto END;
	}

	if (p_data < p_node->p_data)
	{
		p_node->p_left = remove_node(p_node->p_left, p_data);
	}
	else if (p_data > p_node->p_data)
	{
		p_node->p_right = remove_node(p_node->p_right, p_data);
	}
	else
	{
		p_removed = p_node;
		
		if (NULL == p_node->p_left)
		{
			p_node = p_node->p_right;
		}
		else if (NULL == p_node->p_right)
		{
			p_node = p_node->p_left;
		}
		else
		{
			p_node = find_smallest(p_node->p_right);
			p_node->p_right = p_removed->p_right;
			p_node->p_left = p_removed->p_left;
		}
	}

END:
	return p_removed;
}

static node_t * node_find(node_t * p_root, void * p_data)
{
    node_t * p_found = NULL;
	
	if ((NULL == p_root) ||
		(NULL == p_data))
	{
		goto END;
	}
	
	node_t * p_current = p_root;

	if (p_current->p_data == p_data)
	{
		p_found = p_current;
		goto END;
	}

	if (p_current->p_data > p_data)
	{
		p_current = p_current->p_left;
	}
	else
	{
		p_current = p_current->p_right;
	}

	while ((NULL == p_found) ||
		   (NULL == p_current))
	{
		node_find(p_current, p_data);
	}

END:
	return p_found;
}

static void insert_right(node_t * p_node, void * p_data)
{
	if ((NULL == p_node) ||
		(NULL == p_data))
	{
		goto END;
	}

	node_t * new_node = calloc(1, sizeof(node_t));

	if (NULL == new_node)
	{
		goto END;
	}

	new_node->p_data = p_data;
	new_node->p_left = NULL;
	new_node->p_right = NULL;

	p_node->p_right = new_node;

END:
	return;
}

static void insert_left(node_t * p_node, void * p_data)
{
	if ((NULL == p_node) ||
		(NULL == p_data))
	{
		goto END;
	}

	node_t * new_node = calloc(1, sizeof(node_t));

	if (NULL == new_node)
	{
		goto END;
	}

	new_node->p_data = p_data;
	new_node->p_left = NULL;
	new_node->p_right = NULL;

	p_node->p_left = new_node;

END:
	return;
}

static node_t * find_smallest(node_t * p_node)
{
	node_t * p_smallest = NULL;

	if (NULL == p_node)
	{
		goto END;
	}

	p_smallest = p_node;

	while (NULL != p_node->p_left)
	{
		p_smallest = p_smallest->p_left;
	}

END:
	return p_smallest;

}
// end of bst.c
