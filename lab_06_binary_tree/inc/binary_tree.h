#ifndef BIN_TREE_H__
#define BIN_TREE_H__
typedef struct _node_t_
{
    char value;
    struct _node_t_ *left;
    struct _node_t_ *right;
} node_t;

typedef struct _tree_t_
{
    node_t *head;
} tree_t;


tree_t *tree_create(void);

void tree_free(tree_t *tree);
#endif
