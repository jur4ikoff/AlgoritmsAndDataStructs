#include "hash_t_open.h"
#include "constants.h"
#include "errors.h"
#include "hash.h"
#include "menu.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define HASH_TABLE_INIT_SIZE 1

// Всякая всячина для хэш табле
// Статусы элемента
typedef enum
{
    STATE_EMPTY,
    STATE_REMOVED,
    STATE_BUSY
} state_t;

// Один элемент хэш таблицы
struct _open_ht_item_
{
    state_t state; // Состояние
    data_t data;   // Данные
};

// Основная структура для Хэш таблицы
struct _open_ht_type_
{
    struct _open_ht_item_ *table; // Массив данных
    size_t size;                  // Размер
};

/**
 * @brief Создание хэш таблицы
 * @return Хэш таблица
 */
open_ht_t *open_ht_create(size_t size)
{
    open_ht_t *ht = malloc(sizeof(*ht));
    if (ht == NULL)
        return NULL;

    ht->size = size ? size : HASH_TABLE_INIT_SIZE;
    ht->table = calloc(ht->size, sizeof(*ht->table));
    if (ht->table == NULL)
    {
        free(ht);
        return NULL;
    }

    return ht;
}

/**
 * @brief Освобождение памяти из-под хэш таблицы
 * @param[in] ht Указатель на хэш таблицу
 */
void open_ht_free(open_ht_t **ht)
{
    if (ht == NULL || *ht == NULL)
        return;

    free((*ht)->table);
    free(*ht);
    *ht = NULL;
}

error_t open_ht_restruct(open_ht_t **ht, size_t prev_size)
{
    size_t new_size = calc_next_prime(prev_size);
    open_ht_t *new_ht = open_ht_create(new_size);
    if (!new_ht)
    {
        return ERR_MEMORY_ALLOCATION;
    }

    bool need_restruct = false;
    for (size_t i = 0; !need_restruct && i < (*ht)->size; i++)
    {
        if ((*ht)->table[i].state == STATE_EMPTY)
            continue;

        unsigned long long hash = hash_char_first((*ht)->table[i].data.value);
        size_t index = hash % (*ht)->size;
        size_t new_index = index;
        size_t collisions = 0;

        while (((new_ht->table[new_index].state == STATE_BUSY && (*ht)->table[i].data.value - new_ht->table[new_index].data.value != 0) || new_ht->table[new_index].state == STATE_REMOVED) && !need_restruct)
        {
            new_index = (new_index + 1) % (*ht)->size;
            collisions++;
            if (collisions > g_max_collisions)
            {
                need_restruct = true;
            }

            collisions++;
        }

        if (need_restruct)
        {
            goto ex;
        }

        data_t data = (*ht)->table[i].data;
        new_ht->table[new_index].state = STATE_BUSY;
        new_ht->table[new_index].data = data;
    }

    ex:
    if (need_restruct)
    {
        open_ht_free(&new_ht);
        return open_ht_restruct(ht, new_size);
    }

    open_ht_free(ht);
    *ht = new_ht;
    return ERR_OK;
}

error_t open_ht_insert(open_ht_t **ht, data_t element, bool *is_restructured)
{
    if (ht == NULL)
        return ERR_HEAD;

    if (*ht == NULL)
    {
        *ht = open_ht_create(HASH_TABLE_INIT_SIZE);
    }

    if (is_restructured)
        *is_restructured = false;

    error_t rc = ERR_OK;

    unsigned long long hash = hash_char_first(element.value);

    while (true)
    {
        bool need_restruct = false;
        size_t index = hash % (*ht)->size;
        size_t new_index = index;
        size_t collisions = 0;
        while (((*ht)->table[new_index].state == STATE_REMOVED || ((*ht)->table[new_index].state == STATE_BUSY && (*ht)->table[new_index].data.value - element.value != 0)) && !need_restruct)
        {
            new_index = (new_index + 1) % (*ht)->size;
            if (collisions > g_max_collisions)
                need_restruct = true;
            collisions++;
        }

        if (!need_restruct && (*ht)->table[new_index].state == STATE_BUSY)
            return WARNING_REPEAT;

        if (need_restruct)
        {
            if (is_restructured)
                *is_restructured = true;
            if ((rc = open_ht_restruct(ht, (*ht)->size)) != ERR_OK)
                goto err;
        }
        else
        {
            (*ht)->table[new_index].state = STATE_BUSY;
            (*ht)->table[new_index].data = element;
            break;
        }
    }

    err:
    return rc;
}

void open_ht_print(open_ht_t *ht)
{
    for (size_t i = 0; i < ht->size; i++)
    {
        printf("%2zu. ", i);
        switch (ht->table[i].state)
        {
            case STATE_BUSY:
                printf("[Занято] \"%c\"", ht->table[i].data.value);
                break;
            case STATE_EMPTY:
                printf("[Свободно]");
                break;
            case STATE_REMOVED:
                printf("[Удалено]");
                break;
        }
        printf("\n");
    }
}

void open_ht_tree_test(void)
{
    // Инициализация переменных
    printf("\nТестирование хэш таблицы с открытой адресацией\n");
    int test_itteration_count = 0;
    error_t rc = ERR_OK;
    hash_test_menu_t test_operation = TEST_HT_COUNT;
    struct timespec start, end;
    open_ht_t *hash_table = NULL;
    // bool is_first = 1;

    // Запуск главного цикла
    while (test_operation != TEST_HASH_EXIT && rc == ERR_OK)
    {
        // Раз в 4 иттерации выводим меню
        if (test_itteration_count % 4 == 0)
        {
            print_hash_table_menu();
        }
        test_itteration_count++;
        // Ввод операции
        test_operation = input_test_ht_operation();
        if (test_operation == TEST_HASH_EXIT)
        {
            // Тестовая операция выход
            printf("%sУспешный выход из режима тестирования\n%s", GREEN, RESET);
            goto exit;
        }
        else if (test_operation == TEST_HT_LOAD)
        {

            /*char *string_to_convert = malloc(MAX_STRING_LEN * sizeof(char));
            printf("Введите строку для записи в дерево: ");
            fgets(string_to_convert, MAX_STRING_LEN - 1, stdin);

            char *newline = strchr(string_to_convert, '\n');
            if (newline)
                *newline = 0;

            avl_tree_convert_from_string(&tree, string_to_convert);
            is_first = 0;
            free(string_to_convert);*/
        }
        else if (test_operation == TEST_HT_ADD)
        {
            data_t data = { 0 };
            if (input_data(&data, ">>Введите один символ для добавления в хэш таблицу:") != ERR_OK)
            {
                printf("%sОшибка ввода данных%s\n", YELLOW, RESET);
                continue;
            }

            bool is_restructed = false;
            clock_gettime(CLOCK_MONOTONIC_RAW, &start);
            rc = open_ht_insert(&hash_table, data, &is_restructed);
            clock_gettime(CLOCK_MONOTONIC_RAW, &end);
            float time = (end.tv_sec - start.tv_sec) * 1e6f + (end.tv_nsec - start.tv_nsec) / 1e3f;
            if (rc == WARNING_REPEAT)
            {
                print_warning_message(WARNING_REPEAT);
                rc = ERR_OK;
            }
            else
            {
                if (is_restructed)
                    printf("%sДобавлен элемент %c в дерево. Время добавления: %.2f мкс. Реструктуризация не потребовалась%s\n", GREEN, data.value, time, RESET);
                else
                    printf("%sДобавлен элемент %c в дерево. Время добавления: %.2f мкс. Реструктуризация потребовалась%s\n", GREEN, data.value, time, RESET);
            }
        }
        else if (test_operation == TEST_HT_REMOVE)
        {
            /*if (is_first)
            {
                print_warning_message(WARNING_TREE);
                continue;
            }
            data_t data = { 0 };
            if (input_data(&data, "Введите один символ для удаления из дерева:") != ERR_OK)
            {
                printf("%sОшибка ввода данных%s\n", YELLOW, RESET);
                continue;
            }
            clock_gettime(CLOCK_MONOTONIC_RAW, &start);
            tree = avl_tree_remove(tree, data);
            clock_gettime(CLOCK_MONOTONIC_RAW, &end);
            float time = (end.tv_sec - start.tv_sec) * 1e6f + (end.tv_nsec - start.tv_nsec) / 1e3f;
            if (tree)
                printf("%sУдален элемент %c из дерева. Время удаления: %.2f%s\n", GREEN, tree->data.value, time, RESET);
            else
                print_warning_message(WARNING_ELEMENT_NOT_FOUND);*/
        }
        else if (test_operation == TEST_HT_SEARCH)
        {
            /*data_t data = { 0 };
            if (input_data(&data, "Введите один символ для поиска в дереве:") != ERR_OK)
            {
                printf("%sОшибка ввода данных%s\n", YELLOW, RESET);
                continue;
            }

            clock_gettime(CLOCK_MONOTONIC_RAW, &start);
            avl_tree_t *node = avl_tree_search(tree, data);
            clock_gettime(CLOCK_MONOTONIC_RAW, &end);
            float time = (end.tv_sec - start.tv_sec) * 1e6f + (end.tv_nsec - start.tv_nsec) / 1e3f;

            if (node)
            {
                printf("%sЭлемент найден. Время поиска: %.2f%s\n", GREEN, time, RESET);
            }
            else
            {
                print_warning_message(WARNING_ELEMENT_NOT_FOUND);
            }*/
        }
        else if (test_operation == TEST_HT_SHOW)
        {
            // Вывод дерева на экран
            printf("Размер таблицы: %zu\n", hash_table->size);
            open_ht_print(hash_table);
            // avl_tree_show(tree);
        }
        else if (test_operation == TEST_HT_STATS)
        {
            // Статистика о дереве
            // printf("Дерево занимает в памяти %zu байт\n", avl_tree_calc_memory(tree));
            // printf("Среднее количество сравнений %.3f\n", avl_tree_calc_avg_compare(tree));
        }
        else if (test_operation == TEST_HT_UNKNOWN)
        {
            // Операция неизвестна
            print_warning_message(WARNING_OPERATION);
        }
        else if (test_operation == TEST_HT_ERROR)
        {
            printf("%sВыбор неверной операции%s\n", RED, RESET);
            goto exit;
        }
    }

    exit:
    open_ht_free(&hash_table);
}
