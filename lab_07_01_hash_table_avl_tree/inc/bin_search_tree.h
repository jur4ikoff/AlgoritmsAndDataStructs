#ifndef BIN_SEARCH_TREE_H__
#define BIN_SEARCH_TREE_H__

#include "constants.h"

typedef struct _tree_t_ tree_t;

typedef void (*tree_apply_fn_t)(tree_t *subtree, void *arg);

tree_t *tree_create_node(data_t data);
void tree_free(tree_t *tree);

void tree_inorder_traversal(const tree_t *root, int is_head, int is_color);
void preorder_traversal(tree_t *root, int is_head, int is_color);
void postorder_traversal(tree_t *root, int is_head, int is_color);
int tree_insert(tree_t **root, data_t data);
tree_t *tree_search(tree_t *root, data_t data);
int tree_remove(tree_t **root, data_t data);
int tree_in_picture(tree_t *tree);
void tree_search_reset(tree_t *root);

void test_binary_tree(void);
#endif
