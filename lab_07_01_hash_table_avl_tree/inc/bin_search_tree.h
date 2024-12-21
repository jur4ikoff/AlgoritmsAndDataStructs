#ifndef BIN_SEARCH_TREE_H__
#define BIN_SEARCH_TREE_H__

#include "constants.h"

typedef struct _binary_search_tree_t_ bst_tree_t;

typedef void (*tree_apply_fn_t)(bst_tree_t *subtree, void *arg);

bst_tree_t *bin_tree_create_node(data_t data);
void tree_free(bst_tree_t *tree);

void bin_tree_inorder_traversal(const bst_tree_t *root, int is_head, int is_color);
int bin_tree_insert(bst_tree_t **root, data_t data);
bst_tree_t *bin_tree_search(bst_tree_t *root, data_t data);
int bin_tree_remove(bst_tree_t **root, data_t data);
int bin_tree_show(bst_tree_t *tree);
void bin_tree_search_reset(bst_tree_t *root);
void binary_tree_test(void);
#endif
