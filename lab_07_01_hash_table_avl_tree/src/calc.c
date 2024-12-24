#include "calc.h"
#include "avl_tree.h"
#include "hash_t_close.h"
#include "hash_t_open.h"
#include "bin_search_tree.h"
#include "constants.h"
#include "errors.h"
#include "menu.h"
#include "render.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void calc_time_experiment(char *filename, size_t exp_count, size_t size)
{
    size_t ht_close_cmp = 0, ht_open_cmp = 0;
    float bst_cmp = 0, avl_cmp = 0;
    float bst_time = bst_calculte_search_time(filename, exp_count, &bst_cmp);
    float avl_time = avl_calculte_search_time(filename, exp_count, &avl_cmp);
    float ht_close_time = close_ht_calculte_search_time(filename, exp_count, &ht_close_cmp);
    float ht_open_time = open_ht_calculte_search_time(filename, exp_count, &ht_open_cmp);

    printf("Среднее время поиска в дереве из %zu элементов"
           "\nДДП-дерево - %.3f Количество сравнений %.1f"
           "\nAVL-дерево  - %.3f Количество сравнений %.1f\n",
           size, bst_time, bst_cmp, avl_time, avl_cmp);
    printf("Среднее время поиска в хэш-таблице из %zu элементов"
           "\nОткрытая адресация - %.3f Количество сравнений %zu"
           "\nЗакрытая адресация  - %.3f Количество сравнений %zu\n",
           size, ht_open_time, ht_open_cmp, ht_close_time, ht_close_cmp);
}
