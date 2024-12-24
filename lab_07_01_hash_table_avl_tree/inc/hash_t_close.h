#ifndef HT_CHAIN_H__
#define HT_CHAIN_H__

#include "linked_list.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

typedef struct _close_ht_type_ close_ht_t;

// Создание таблицы
close_ht_t *close_ht_create(size_t size);
// Освобождение памяти и удаление всех элементов
void close_ht_free(close_ht_t **ht);
// Очистка памяти из-под всех элементов
int close_ht_clear(close_ht_t *ht);

// реструктуризация
int close_ht_restruct(close_ht_t **ht);

// Основные функции для работы с хэш таблицой
int close_ht_insert(close_ht_t **ht, data_t *data, bool *is_restruct);
int close_ht_remove(close_ht_t *ht, data_t *data);
int close_ht_search(const close_ht_t *ht, data_t *data, size_t *cmp);

// Вывод на экран
void close_ht_print(const close_ht_t *ht);

float close_ht_calc_avg_compare(close_ht_t *ht);
// Замер памяти
size_t close_ht_calc_memory(close_ht_t *ht);

int close_ht_convert_from_string(close_ht_t **ht, char *string);
// Тестирование
void close_ht_test(void);
float close_ht_calculte_search_time(char *filename, size_t exp_count, size_t *cmp);
extern size_t g_max_collisions;

#endif // HT_CHAIN_H__
