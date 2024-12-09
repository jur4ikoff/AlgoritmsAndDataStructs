#ifndef TASK_H__
#define TASK_H__
#include "binary_tree.h"

void convert_string_to_tree(tree_t **tree, const char *string);
void tree_delete_repeat(tree_t **tree);
void remove_duplicates(tree_t **node);
void string_remove_duplicates(char *str);
#endif