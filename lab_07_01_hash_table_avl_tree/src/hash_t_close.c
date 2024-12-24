#include "hash_t_close.h"
#include "constants.h"
#include "hash.h"
#include "linked_list.h"
#include "menu.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct _close_ht_type_
{
    list_t **table; // Массив листов
    size_t size;    // размер
};

close_ht_t *close_ht_create(size_t size)
{
    close_ht_t *ht = malloc(sizeof(*ht));
    if (ht == NULL)
        return NULL;

    ht->size = size ? size : HT_INIT_SIZE;
    ht->table = calloc(ht->size, sizeof(*ht->table));
    if (ht->table == NULL)
    {
        free(ht);
        return NULL;
    }

    return ht;
}

static bool close_ht_check_need_restruct(const close_ht_t *ht)
{
    // Вместо проверки на ht
    assert(ht);

    for (size_t i = 0; i < ht->size; i++)
        if (list_size(ht->table[i]) > g_max_collisions)
            return true;

    return false;
}

int close_ht_restruct(close_ht_t **ht)
{
    if (!close_ht_check_need_restruct(*ht))
        return WARNING_NO_RESTRUCT;

    close_ht_t *new_ht = NULL;
    size_t cur_size = (*ht)->size;
    int rc = ERR_OK;
    do
    {
        size_t new_size = calc_next_prime(cur_size);
        close_ht_free(&new_ht);
        new_ht = close_ht_create(new_size);
        if (new_ht == NULL)
        {
            rc = ERR_MEMORY_ALLOCATION;
            goto err;
        }

        for (size_t i = 0; i < (*ht)->size; i++)
        {
            list_t *cur = (*ht)->table[i];
            while (cur != NULL)
            {
                size_t hash = hash_char_first(cur->data->value);
                size_t ind = hash % new_ht->size;
                if ((rc = list_push_back(&new_ht->table[ind], cur->data)) != ERR_OK)
                    goto err;
                cur = cur->next;
            }
        }
        cur_size = new_size;
    } while (close_ht_check_need_restruct(new_ht));

err:
    if (rc != ERR_OK)
    {
        close_ht_clear(new_ht);
        free(new_ht->table);
        free(new_ht);
    }
    else
    {
        free((*ht)->table);
        free(*ht);

        *ht = new_ht;
    }
    return rc;
}

void close_ht_free(close_ht_t **ht)
{
    if (ht == NULL || *ht == NULL)
        return;

    for (size_t i = 0; i < (*ht)->size; i++)
        list_free((*ht)->table + i);

    free((*ht)->table);
    free(*ht);

    *ht = NULL;
}

int close_ht_insert(close_ht_t **ht, data_t *data, bool *is_restruct)
{
    if (ht == NULL || data == NULL)
        return ERR_HEAD;

    if (*ht == NULL)
        *ht = close_ht_create(HT_INIT_SIZE);

    size_t hash = hash_char_first(data->value);
    size_t index = hash % (*ht)->size;

    if (list_search_by_key((*ht)->table[index], data, NULL) != NULL)
    {
        (*ht)->table[index]->data->repeat++;
        return WARNING_REPEAT;
    }

    int rc = list_push_back(&(*ht)->table[index], data);
    if (rc != ERR_OK)
        return rc;

    if (is_restruct)
        *is_restruct = false;

    rc = close_ht_restruct(ht);
    if (is_restruct && rc == ERR_OK)
        *is_restruct = true;

    if (rc == WARNING_NO_RESTRUCT)
        rc = ERR_OK;

    return rc;
}

int close_ht_search(const close_ht_t *ht, data_t *data, size_t *cmp)
{
    if (ht == NULL || ht == NULL)
        return ERR_HEAD;

    size_t hash = hash_char_first(data->value);
    size_t index = hash % ht->size;

    list_t *node = (list_t *)list_search_by_key(ht->table[index], data, cmp);
    if (node == NULL)
        return WARNING_ELEMENT_NOT_FOUND;

    return ERR_OK;
}

int close_ht_remove(close_ht_t *ht, data_t *data)
{
    if (ht == NULL)
        return ERR_HEAD;

    size_t hash = hash_char_first(data->value);
    size_t index = hash % ht->size;

    return list_remove_by_key(&ht->table[index], data);
}

// Очистка памяти из-под всех элементов
int close_ht_clear(close_ht_t *ht)
{
    if (ht == NULL)
        return ERR_HEAD;

    for (size_t i = 0; i < ht->size; i++)
        list_free_without_data(&ht->table[i]);

    return ERR_OK;
}

static size_t calc_sum_1_to_num(size_t num)
{
    size_t sum = 0;

    for (size_t i = 0; i <= num; i++)
        sum += i;

    return sum;
}

float close_ht_calc_avg_compare(close_ht_t *ht)
{
    float res = 0;
    size_t count = 0;
    for (size_t i = 0; i < ht->size; i++)
    {
        size_t size = list_size(ht->table[i]);
        size_t sum = calc_sum_1_to_num(size);
        res += sum;
        count += size;
    }

    return res / count;
}

size_t close_ht_calc_memory(close_ht_t *ht)
{
    size_t size = sizeof(close_ht_t);
    for (size_t i = 0; i < ht->size; i++)
        size += list_size(ht->table[i]) * sizeof(**ht->table);

    return size;
}

void close_ht_print(const close_ht_t *ht)
{
    for (size_t i = 0; i < ht->size; i++)
    {
        printf("%02zu. ", i);
        if (ht->table[i] == NULL)
            printf("NULL");
        else
            list_print(ht->table[i]);
        printf("\n");
    }
}

int close_ht_convert_from_string(close_ht_t **ht, char *string)
{
    if (ht == NULL || string == NULL)
        return ERR_HEAD;

    char *ptr = string;
    while (*ptr)
    {
        data_t *data = calloc(1, sizeof(data_t));
        data->value = *ptr;
        bool is = false;
        close_ht_insert(ht, data, &is);
        (void)is;
        ptr++;
    }
    return ERR_OK;
}

void close_ht_test(void)
{
    // Инициализация переменных
    printf("\nТестирование хэш таблицы с открытой адресацией\n");
    int test_itteration_count = 0;
    error_t rc = ERR_OK;
    hash_test_menu_t test_operation = TEST_HT_COUNT;
    struct timespec start, end;
    close_ht_t *hash_table = NULL;
    bool is_first = 1;

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
            char *string_to_convert = malloc(MAX_STRING_LEN * sizeof(char));
            printf("Введите строку для записи в хэш таблицу: ");
            fgets(string_to_convert, MAX_STRING_LEN - 1, stdin);

            char *newline = strchr(string_to_convert, '\n');
            if (newline)
                *newline = 0;

            close_ht_convert_from_string(&hash_table, string_to_convert);
            is_first = 0;
            free(string_to_convert);
        }
        else if (test_operation == TEST_HT_ADD)
        {
            data_t *data = calloc(1, sizeof(data_t));
            if (input_data(data, ">>Введите один символ для добавления в хэш таблицу:") != ERR_OK)
            {
                printf("%sОшибка ввода данных%s\n", YELLOW, RESET);
                continue;
            }

            printf("%c\n", data->value);
            bool is_restructed = false;
            clock_gettime(CLOCK_MONOTONIC_RAW, &start);
            rc = close_ht_insert(&hash_table, data, &is_restructed);
            clock_gettime(CLOCK_MONOTONIC_RAW, &end);
            float time = (end.tv_sec - start.tv_sec) * 1e6f + (end.tv_nsec - start.tv_nsec) / 1e3f;
            if (rc == WARNING_REPEAT)
            {
                print_warning_message(WARNING_REPEAT);
                rc = ERR_OK;
            }
            else
            {
                is_first = 0;
                if (is_restructed)
                    printf("%sДобавлен элемент %c в дерево. Время добавления: %.2f мкс. Реструктуризация не потребовалась%s\n", GREEN, data->value, time, RESET);
                else
                    printf("%sДобавлен элемент %c в дерево. Время добавления: %.2f мкс. Реструктуризация потребовалась%s\n", GREEN, data->value, time, RESET);
            }
        }
        else if (test_operation == TEST_HT_REMOVE)
        {
            if (is_first)
            {
                print_warning_message(WARNING_TREE);
                continue;
            }
            data_t *data = calloc(1, sizeof(data_t));
            if (input_data(data, "Введите один символ для удаления из дерева:") != ERR_OK)
            {
                printf("%sОшибка ввода данных%s\n", YELLOW, RESET);
                continue;
            }
            clock_gettime(CLOCK_MONOTONIC_RAW, &start);
            rc = close_ht_remove(hash_table, data);
            clock_gettime(CLOCK_MONOTONIC_RAW, &end);
            float time = (end.tv_sec - start.tv_sec) * 1e6f + (end.tv_nsec - start.tv_nsec) / 1e3f;
            if (rc == ERR_OK)
                printf("%sУдален элемент %c из дерева. Время удаления: %.2f%s\n", GREEN, data->value, time, RESET);
            else
            {
                print_warning_message(WARNING_ELEMENT_NOT_FOUND);
                rc = ERR_OK;
            }
        }
        else if (test_operation == TEST_HT_SEARCH)
        {
            data_t *data = calloc(1, sizeof(data_t));
            if (input_data(data, "Введите один символ для поиска в дереве:") != ERR_OK)
            {
                printf("%sОшибка ввода данных%s\n", YELLOW, RESET);
                continue;
            }
            size_t cmp = 0;
            clock_gettime(CLOCK_MONOTONIC_RAW, &start);
            rc = close_ht_search(hash_table, data, &cmp);
            clock_gettime(CLOCK_MONOTONIC_RAW, &end);
            float time = (end.tv_sec - start.tv_sec) * 1e6f + (end.tv_nsec - start.tv_nsec) / 1e3f;

            if (rc == ERR_OK)
            {
                printf("%sЭлемент найден. Время поиска: %.2f Количество сравнение %zu%s\n", GREEN, time, cmp, RESET);
            }
            else
            {
                print_warning_message(WARNING_ELEMENT_NOT_FOUND);
                rc = ERR_OK;
            }
        }
        else if (test_operation == TEST_HT_SHOW)
        {
            // Вывод дерева на экран
            printf("Размер таблицы: %zu\n", hash_table->size);
            close_ht_print(hash_table);
        }
        else if (test_operation == TEST_HT_STATS)
        {
            // Статистика о дереве
            printf("Хэш таблица занимает в памяти %zu байт\n", close_ht_calc_memory(hash_table));
            printf("Среднее количество сравнений %.3f\n", close_ht_calc_avg_compare(hash_table));
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
    close_ht_free(&hash_table);
}

float close_ht_calculte_search_time(char *filename, size_t exp_count, size_t *cmp)
{
    struct timespec start, end;
    float time_del = 0.0;
    char *result = malloc(MAX_STRING_LEN * sizeof(char));
    int rc = ERR_OK;
    if ((rc = input_string_from_file(filename, result)) != ERR_OK)
    {
        free(result);
        return rc;
    }

    close_ht_t *ht = NULL;
    close_ht_convert_from_string(&ht, result);
    if (!ht)
    {
        close_ht_free(&ht);
        free(result);
        return ERR_STRING;
    }

    size_t count = 0;
    for (size_t i = 0; i < exp_count; i++)
    {
        char *ptr = result;
        while (*ptr)
        {
            data_t *data = calloc(1, sizeof(data_t));
            data->value = *ptr;
            clock_gettime(CLOCK_MONOTONIC_RAW, &start);
            close_ht_search(ht, data, cmp);
            clock_gettime(CLOCK_MONOTONIC_RAW, &end);
            time_del += (end.tv_sec - start.tv_sec) * 1e6f + (end.tv_nsec - start.tv_nsec) / 1e3f;
            free(data);
            count++;
            ptr++;
        }
    }

    free(result);
    return time_del / count;
}
