#ifndef TASK_H__
#define TASK_H__
#include "binary_tree.h"

void convert_string_to_tree(tree_t **tree, char *string);
void tree_delete_repeat(tree_t **tree);
void remove_duplicates(tree_t **node);
void string_remove_duplicates(char *str);
void tree_repeat_test(tree_t **tree);
#endif
