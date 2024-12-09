#include "binary_tree.h"
#include <stdlib.h>

/*tree_t *tree_create(void)
{
   tree_t *tree = malloc(sizeof(tree_t));
    if (!tree)
        return NULL;

    tree->head = NULL;
    return tree;

}*/

void tree_free(tree_t *tree)
{
    free(tree);
}
