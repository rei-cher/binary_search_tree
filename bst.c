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
static node_t * node_find(bst_t * p_bst, node_t * p_root, void * p_data);
static node_t * find_smallest(node_t * p_node);
static node_t * remove_node(bst_t * p_bst, node_t * p_node, void * p_data, void ** pp_removed);
static void insert_left(node_t * p_node, void * p_data);
static void insert_right(node_t * p_node, void * p_data);
static void print_order(node_t * p_node, print_f p_print);

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
		(NULL == p_data))
	{
		goto END;
	}

	if (NULL == p_bst->p_root)
	{
		node_t * p_new_node = calloc(1, sizeof(node_t));
	
		if (NULL == p_new_node)
		{
			goto END;
		}

		p_new_node->p_data = p_data;
		p_new_node->p_left = NULL;
		p_new_node->p_right = NULL;

		p_bst->p_root = p_new_node;

		p_bst->size++;

		SUCCESS = 0;
		goto END;
	}
	
	node_t * p_tmp = NULL;
	node_t * p_current = p_bst->p_root;

	while (NULL != p_current)
	{
		p_tmp = p_current;

		if (0 < p_bst->p_comp(p_current->p_data, p_data))
		{
			p_current = p_current->p_left;
		}
		else if (0 > p_bst->p_comp(p_current->p_data, p_data))
		{
			p_current = p_current->p_right;
		}
		else
		{
			goto END;
		}
	}

	if (0 < p_bst->p_comp(p_tmp->p_data, p_data))
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
	void * p_removed = NULL;

	if ((NULL == p_bst) ||
		(NULL == p_data) ||
		(NULL == p_bst->p_root))
	{
		goto END;
	}

	p_bst->p_root = remove_node(p_bst, p_bst->p_root, p_data, &p_removed);
	
	if (NULL != p_removed)
	{
		p_bst->size--;
	}

END:
	return p_removed;
}

void bst_inorder_print(bst_t * p_bst, print_f p_print)
{
	if ((NULL == p_bst) ||
		(NULL == p_bst->p_root))
	{
		goto END;
	}

	print_order(p_bst->p_root, p_print);

END:
	return;
}

static void print_order(node_t * p_node, print_f p_print)
{
	if (NULL == p_node)
	{
		goto END;
	}

	print_order(p_node->p_left, p_print);
	p_print(p_node->p_data);
	print_order(p_node->p_right, p_print);

END:
	return;
}

int bst_search(bst_t * p_bst, void * p_data)
{
	int SUCCESS = 1;

	if ((NULL == p_bst) ||
		(NULL == p_data) ||
		(NULL == p_bst->p_root) ||
		(NULL == node_find(p_bst, p_bst->p_root, p_data)))
	{
		goto END;
	}
	
	SUCCESS = 0;

END:
	return SUCCESS;
}

int bst_size(bst_t * p_bst)
{
	int size = 0;

	if ((NULL == p_bst) ||
		(NULL == p_bst->p_root))
	{
		goto END;
	}

	size = p_bst->size;

END:
	return size;
}

// TODO: static function definitions here
static node_t * remove_node(bst_t * p_bst, node_t * p_node, void * p_data, void ** pp_removed)
{
	if ((NULL == p_bst) ||
		(NULL == p_node) ||
		(NULL == p_data) ||
		(NULL == pp_removed))
	{
		goto END;
	}

	if (0 < p_bst->p_comp(p_node->p_data, p_data))
	{
		p_node->p_left = remove_node(p_bst, 
									 p_node->p_left, 
									 p_data, 
									 pp_removed);
	}
	else if (0 > p_bst->p_comp(p_node->p_data, p_data))
	{
		p_node->p_right = remove_node(p_bst, 
									  p_node->p_right, 
									  p_data, 
									  pp_removed);
	}
	else
	{
		(* pp_removed) = p_node->p_data;

		if (NULL == p_node->p_left)
		{
			node_t * p_right = p_node->p_right;
			free(p_node);
			p_node = p_right;
			goto END;
		}

		if (NULL == p_node->p_right)
		{
			node_t * p_left = p_node->p_left;
			free(p_node);
			p_node = p_left;
			goto END;
		}

		node_t * p_smallest = find_smallest(p_node->p_right);
		p_node->p_data = p_smallest->p_data;
		
		void * p_tmp = NULL;
		
		p_node->p_right = remove_node(p_bst, p_node->p_right, p_smallest->p_data, &p_tmp);
	}

END:
	return p_node;
}

static node_t * node_find(bst_t * p_bst, node_t * p_node, void * p_data)
{
    node_t * p_found = NULL;
	
	if ((NULL == p_bst) ||
		(NULL == p_node) ||
		(NULL == p_data))
	{
		goto END;
	}
	
	node_t * p_current = p_node;

	if (0 < p_bst->p_comp(p_node->p_data, p_data))
	{
		p_current = p_current->p_left;
	}
	else if (0 > p_bst->p_comp(p_node->p_data, p_data))
	{
		p_current = p_current->p_right;
	}
	else
	{
		p_found = p_current;
		goto END;
	}
	
	p_found = node_find(p_bst, p_current, p_data);


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

	while (NULL != p_smallest->p_left)
	{
		p_smallest = p_smallest->p_left;
	}

END:
	return p_smallest;

}
// end of bst.c
