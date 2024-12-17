#ifndef BIN_SEARCH_TREE_H__
#define BIN_SEARCH_TREE_H__

#include "constants.h"

typedef struct _binary_search_tree_t_ tree_t;

typedef void (*tree_apply_fn_t)(tree_t *subtree, void *arg);

tree_t *bin_tree_create_node(data_t data);
void tree_free(tree_t *tree);

void bin_tree_inorder_traversal(const tree_t *root, int is_head, int is_color);
void preorder_traversal(tree_t *root, int is_head, int is_color);
void postorder_traversal(tree_t *root, int is_head, int is_color);
int bin_tree_insert(tree_t **root, data_t data);
tree_t *bin_tree_search(tree_t *root, data_t data);
int bin_tree_remove(tree_t **root, data_t data);
int bin_tree_in_picture(tree_t *tree);
void bin_tree_search_reset(tree_t *root);

void test_binary_tree(void);
#endif
