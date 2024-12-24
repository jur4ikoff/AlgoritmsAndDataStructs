#ifndef BIN_SEARCH_TREE_H__
#define BIN_SEARCH_TREE_H__

#include "constants.h"
#include <stdio.h>

typedef struct _binary_search_tree_t_ bst_tree_t;

typedef void (*bst_tree_apply_fn_t)(bst_tree_t *subtree, void *arg);

bst_tree_t *bin_tree_create_node(data_t data);
void bin_tree_free(bst_tree_t *tree);

void bin_tree_inorder_traversal(const bst_tree_t *root, int is_head, int is_color);
int bin_tree_insert(bst_tree_t **root, data_t data);
bst_tree_t *bin_tree_search(bst_tree_t *root, data_t data);
int bin_tree_remove(bst_tree_t **root, data_t data);
int bst_tree_show(bst_tree_t *tree, char *img_file);
void bin_tree_search_reset(bst_tree_t *root);
size_t bin_tree_calc_memory(bst_tree_t *root);
float bin_tree_calc_avg_compare(bst_tree_t *root);
float bst_calculte_search_time(char *filename, size_t exp_count, float *cmp);
void binary_tree_test(void);
void bin_tree_convert_from_string(bst_tree_t **tree, char *string);
bst_tree_t *bst_tree_search_with_cmp(bst_tree_t *root, data_t data, size_t *cmp);
void tree_remove_repeat(bst_tree_t **tree);
#endif
