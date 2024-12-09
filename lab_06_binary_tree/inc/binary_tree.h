#ifndef BIN_TREE_H__
#define BIN_TREE_H__

typedef char data_t;

typedef struct _tree_t_
{
    data_t data;
    int is_repeated; // 0 - not repeat; 1 - repeat
    struct _tree_t_ *left;
    struct _tree_t_ *right;
} tree_t;

tree_t *tree_create_node(data_t data);
void tree_free(tree_t *tree);

void inorder_traversal(const tree_t *root, int is_head);
int tree_insert(tree_t **root, data_t data);

int tree_remove(tree_t **root, data_t data);
#endif
