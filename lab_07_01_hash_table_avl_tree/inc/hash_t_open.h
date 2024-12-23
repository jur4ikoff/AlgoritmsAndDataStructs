#ifndef HASH_TABLE_H__
#define HASH_TABLE_H__

#include "constants.h"
#include <stdio.h>

typedef struct _open_ht_type_ open_ht_t;

// Функция для тестирования Hash таблицы на открытой адрессации
void open_ht_tree_test(void);

// Создание таблицы ht;
open_ht_t *open_ht_create(size_t size);
// Освобождение памяти из-под хэш таблицы
void open_ht_free(open_ht_t **ht);


extern size_t g_max_collisions;
#endif
