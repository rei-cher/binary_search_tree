# YOU SHOULD NOT PUSH ANY MODIFICATION TO THE FILES IN THIS DIRECTORY

- If you identify a problem with any of the tests in this directory, make an issue on your repo.

## bst_tests.c
- my_int_compare() - this function works as a compare function for when the binary search tree holds integer pointers.

- my_print() - this function is a print function for simple integers. It is used to verify that you are actually inserting nodes into the tree in the correct way. If your tree is built correctly, you won't actually see any prints from this function. You will only see the in order traversal printed out if your tree is messed up. The `bst.c` file that I used to validate these tests cases would would always grab the minimum value of the right child tree when you remove a node with both left and right children (as opposed to always grabbing the maximum of the left child tree), but it shouldn't matter what your tree does.

- my_assert_string() - this function is just a wrapper around the string assert since the built in string assert doesn't show you what string you had versus what was expected.

- If you remove `-fsanitize=address` from your compilation flags. You can run the entire test suite in valgrind as well to make sure that you are not leaking any memory.

Here is a breakdown of the tests in this file. They are broken down into 2 suites. The first suite tests all functions except the bst_inorder_print(). The second suite tests that the actual order of nodes in the tree is correct through bst_inorder_print().

### test_create_destroy_empty()
This test validates the create function and destruction of an empty tree.

- p_bst should be successfully created when the create function is given a comparison function and no free function. p_bst is checked to be non NULL. p_bst should then be successfully destroyed. p_bst is then checked to be NULL.
- p_bst2 should be successfully created when the create function is given a comparison function and a free function. p_bst2 is checked to be non NULL. p_bst2 should then be successfully destroyed. p_bst2 is then checked to be NULL.
- p_bst3 should not be created when the create function is given no comparison function and a free function. p_bst3 is checked to be NULL. NULL is then given to the destroy function, with the expectation that nothing happens.
- p_bst4 should not be created when the create function is given no comparison function and no free function. p_bst4 is checked to be NULL.

### test_insert_remove_stack()
This test validates the insert and remove functions. To start, a valid binary search tree is created without a free function.

#### Null Checks
- The first test makes sure that passing NULL as the binary search tree pointer to the insert function returns `EXIT_FAILURE`.
- The second test makes sure that passing NULL as the data pointer to the insert function returns `EXIT_FAILURE`.

#### Insert and Remove
- The next 10 checks make sure that 5 pointers to integers can be added and then successfully removed.

#### Remove Data that doesn't Exist
- The next 5 checks make sure that the 5 pointers to integers that have already been removed from the binary search tree can't be removed again.

#### Add Duplicate Data
- The next 2 checks makes sure that once the pointer to integer `1` is successfully added to the binary search tree that it can't be added a second time.
- These two checks are then repeated for pointers to the integers `-1` and `0`.

The 3 pointers to integers `-1`, `0`, and `1` are then removed from the binary search tree and then the tree is destroyed.

### test_insert_remove_heap()
The same tests are repeated as test_insert_remove_stack(), but the data given to the binary search tree is now heap allocated.

### test_destroy_nonempty()
- The first test validates that a binary search tree with stack allocated data is properly destroyed.
- The second test validates that a tree with heap allocated data is properly freed and destroyed.

### test_search_stack()
- This starts with a test that checks that passing NULL as the  pointer to the tree returns `EXIT_FAILURE`.
- The first group of tests validate that stack allocated integers that are in the tree can be found.
- The second group of tests validate that stack allocated integers that are not in the tree are not found.

### test_search_heap()
- The tests for test_search_stack are repeated using heap allocated integers.

### test_size()
- These tests make sure that the size function returns the correct size as the tree grows and shrinks.


The following suite relies on the bst_inorder_print() function to work. The following is tested:

### test_inorder_simple()
- Most straight forward insertion: 5 -> 3 -> 7 -> 2 -> 4 -> 6 -> 8 . (The inserted nodes build a full tree).

### test_always_left()
- Always add a lesser node 8 -> 7 -> 6 -> 5 -> 4 -> 3 -> 2.

### test_always_right()
- Always add a greater node 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8.

### test_random()
- Some random order that I made up.

### test_remove_simple()
- Removes the nodes in reverse order of insertion from test_inorder_simple() checking that the print is good after each removal.

### test_remove_root_min_right()
- Always removes the root node then the minimum of the remaining right tree.

### test_remove_root_max_left()
- Always removes the root node then the maximum of the remaining left tree.
