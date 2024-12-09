#ifndef BIN_TREE_H__
#define BIN_TREE_H__

typedef char data_t;

typedef struct _tree_t_
{
    data_t data;
    int is_repeated;
    struct _tree_t_ *left;
    struct _tree_t_ *right;
} tree_t;

// tree_t *tree_create(void);

void tree_free(tree_t *tree);
#endif
