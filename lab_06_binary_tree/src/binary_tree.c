#include "binary_tree.h"
#include "constants.h"
#include "errors.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

tree_t *tree_create_node(data_t data)
{
    tree_t *node = malloc(sizeof(tree_t));

    if (!node)
        return NULL;

    node->data = data;
    node->is_repeated = 0;
    node->is_search = 0;
    node->left = NULL;
    node->right = NULL;
    return node;
}

/**
 * @brief Функция вставляет элемент в дерево поиска
 * @param root Корень дерева
 * @param data Структура данных, которую нужно вставить
 */
int tree_insert(tree_t **root, data_t data)
{
    int rc = ERR_OK;
    if (!data)
        return ERR_DATA_INPUT;

    if (!(*root))
    {
        *root = tree_create_node(data);
        return ERR_OK;
    }

    int cmp = data - (*root)->data;

    if (cmp == 0)
    {
        (*root)->is_repeated = 1;
        return WARNING_REPEAT;
    }
    else if (cmp > 0)
        rc = tree_insert(&(*root)->right, data);
    else
        rc = tree_insert(&(*root)->left, data);

    return rc;
}

// Удалить ноду
int tree_remove(tree_t **root, data_t data)
{
    if (!(*root))
        return WARNING_TREE;

    int cmp = data - (*root)->data;
    if (cmp > 0)
    {
        return tree_remove(&(*root)->right, data);
    }
    else if (cmp < 0)
    {
        return tree_remove(&(*root)->left, data);
    }
    if (cmp == 0)
    {
        tree_t *temp = *root;
        if (!(*root)->left && !(*root)->right)
        {
            free(*root);
            *root = NULL;
        }
        else if ((*root)->left == NULL)
        {
            *root = (*root)->right;
            free(temp);
        }
        else if ((*root)->right == NULL)
        {
            *root = (*root)->left;
            free(temp);
        }
        else
        {
            tree_t *min_node = (*root)->right;
            while (min_node && min_node->left)
            {
                min_node = min_node->left;
            }

            (*root)->data = min_node->data;
            return tree_remove(&(*root)->right, min_node->data);
        }
    }
    else
        return WARNING_NO_EL;
    return ERR_OK;
}

tree_t *tree_search(tree_t *root, data_t data)
{
    if (root == NULL)
    {
        return root;
    }

    if (data == root->data)
    {
        root->is_search = 1;
        return root;
    }

    if (data > root->data)
    {
        return tree_search(root->right, data);
    }
    else
    {
        return tree_search(root->left, data);
    }

    return root;
}

void tree_free(tree_t *tree)
{
    if (!tree)
        return;

    tree_free(tree->left);
    tree_free(tree->right);
    free(tree);
}

/**
 * @brief Функция для инфиксного обхода дерева
 * @param root Указатель на корень
 * @param is_head Специальный флаг, нужен для того, чтобы вовремя вывести \n
 * @return
 */
void inorder_traversal(const tree_t *root, int is_head, int is_color)
{
    if (root != NULL)
    {
        inorder_traversal(root->left, 0, is_color);
        if (is_color)
        {
            if (root->is_search)
                printf("%s%c%s ", GREEN, root->data, RESET);
            else if (root->is_repeated)
                printf("%s%c%s ", RED, root->data, RESET);
            else
                printf("%c ", root->data);
        }
        else
            printf("%c ", root->data);
        inorder_traversal(root->right, 0, is_color);
    }

    if (is_head > 0)
        printf("\n");
}

// Префиксный обход дерева
void preorder_traversal(tree_t *root, int is_head, int is_color)
{
    if (!root)
        return;

    if (is_color)
    {
        if (root->is_search)
            printf("%s%c%s ", GREEN, root->data, RESET);
        else if (root->is_repeated)
            printf("%s%c%s ", RED, root->data, RESET);
        else
            printf("%c ", root->data);
    }
    else
        printf("%c ", root->data);
    preorder_traversal(root->left, 0, is_color);
    preorder_traversal(root->right, 0, is_color);

    if (is_head > 0)
    {
        printf("\n");
    }
}

// Постфиксный обход дерева
void postorder_traversal(tree_t *root, int is_head, int is_color)
{
    if (root != NULL)
    {
        postorder_traversal(root->left, 0, is_color);
        postorder_traversal(root->right, 0, is_color);
        if (is_color)
        {
            if (root->is_search)
                printf("%s%c%s ", GREEN, root->data, RESET);
            else if (root->is_repeated)
                printf("%s%c%s ", RED, root->data, RESET);
            else
                printf("%c ", root->data);
        }
        else
            printf("%c ", root->data);
    }

    if (is_head > 0)
    {
        printf("\n");
    }
}

// Функция очищает найденную ноду
void tree_search_reset(tree_t *root)
{
    if (root != NULL)
    {
        tree_search_reset(root->left);
        root->is_search = 0;
        tree_search_reset(root->right);
    }
}

static void to_dot(tree_t *tree, void *file)
{
    static int null_cnt = 0;

    if (tree->is_search)
        fprintf(file, "  %c [color=\"green\"];\n", tree->data);

    if (tree->is_repeated)
        fprintf(file, "  %c [color=\"red\"];\n", tree->data);

    if (tree->left)
        fprintf(file, "  %c -> %c;\n", tree->data, tree->left->data);
    else
    {
        fprintf(file, "  %c -> null_%d;\n", tree->data, null_cnt);
        fprintf(file, "  null_%d [shape=\"point\", color=\"red\"];\n", null_cnt);
        null_cnt++;
    }

    if (tree->right)
        fprintf(file, "  %c -> %c;\n", tree->data, tree->right->data);
    else
    {
        fprintf(file, "  %c -> null_%d;\n", tree->data, null_cnt);
        fprintf(file, "  null_%d [shape=\"point\", color=\"red\"];\n", null_cnt);
        null_cnt++;
    }
}

void tree_apply_pre(tree_t *tree, tree_apply_fn_t apply_fn, void *arg)
{
    if (!tree)
        return;

    apply_fn(tree, arg);
    tree_apply_pre(tree->left, apply_fn, arg);
    tree_apply_pre(tree->right, apply_fn, arg);
}


void tree_to_graphviz(FILE *file, const char *tree_name, tree_t *tree)
{
    fprintf(file, "digraph %s {\n", tree_name);
    tree_apply_pre(tree, to_dot, file);
    fprintf(file, "}\n");
}

static int open_img(const char *img)
{
    pid_t pid = fork();
    if (pid == -1)
        return ERR_FORK;

    if (pid == 0)
    {
        int stdout_file = open("/dev/null", O_RDWR);
        if (dup2(stdout_file, STDERR_FILENO) == -1) // redirect fork'ed process stderr to /dev/null
            goto err;

        //     |> exec_name
        //     |       |> argv      |> it's necessary
        execlp("open", "open", img, NULL);

        err:
        close(stdout_file);

        perror("execlp");
        _exit(EXIT_FAILURE);
    }
    else
    {
        int ret_code;
        waitpid(pid, &ret_code, 0);
        if (WEXITSTATUS(ret_code) != 0)
            return ERR_FORK;
    }
    return ERR_OK;
}

int tree_in_picture(tree_t *tree)
{
    const char *gp = "temp.gp";
    const char *img = "tmp.png";

    FILE *file = fopen(gp, "w");
    if (!file)
        return ERR_FILE;

    tree_to_graphviz(file, "tree", tree);

    fclose(file);

    pid_t pid = fork();
    if (pid == -1)
        return ERR_FORK;

    if (pid == 0)
    {
        execlp("dot", "dot", "-Tpng", gp, "-o", img, NULL);
        perror("execlp");
        _exit(EXIT_FAILURE);
    }
    else
    {
        int ret_code;
        waitpid(pid, &ret_code, 0);
        if (WEXITSTATUS(ret_code) != 0)
            return ERR_FORK;
    }
    return open_img(img);
}
