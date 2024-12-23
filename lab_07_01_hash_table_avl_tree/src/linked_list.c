#include "linked_list.h"
#include "errors.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Создает узел односвязного списка
 *
 * @return list_t* Указатель на узел
 */
list_t *list_node_create(void)
{
    list_t *new_node = malloc(sizeof(*new_node));
    if (new_node)
    {
        new_node->data = NULL;
        new_node->next = NULL;
    }

    return new_node;
}

/**
 * @brief Добавляет в конец списка элемент
 *
 * @param head Двойной указатель на голову
 * @param key Ключ
 * @param val Значение
 * @return int Код ошибки
 */
int list_push_back(list_t **head, data_t *data)
{
    list_t *new_node = list_node_create();
    if (new_node == NULL || data == NULL)
        return ERR_MEMORY_ALLOCATION;

    new_node->data = data;

    if (*head == NULL)
    {
        *head = new_node;
    }
    else
    {
        list_t *tmp = *head;
        while (tmp->next != NULL)
            tmp = tmp->next;

        tmp->next = new_node;
    }

    return ERR_OK;
}

/**
 * @brief Освобождает память из-под списка
 *
 * @param head Двойной указатель на голову
 */
void list_free(list_t **head)
{
    list_t *temp = *head;
    while (temp)
    {
        list_t *next = temp->next;
        free(temp->data);
        free(temp);
        temp = next;
    }

    *head = NULL;
}

/**
 * @brief Освобождает память из-под списка без очистки данных
 *
 * @param head Двойной указатель на голову
 */
void list_free_without_data(list_t **head)
{
    list_t *temp = *head;
    while (temp)
    {
        list_t *next = temp->next;
        free(temp);
        temp = next;
    }

    *head = NULL;
}



/**
 * @brief Применяет функцию к каждому узлу списка
 *
 * @param head Указатель на голову
 * @param func Указатель на функцию
 * @param arg Параметр для функции
 */
void list_apply(list_t *head, list_func_t func, void *arg)
{
    list_t *tmp = head;
    while (tmp != NULL)
    {
        func(tmp, arg);
        tmp = tmp->next;
    }
}

/**
 * @brief Ищет в односвязном списке узел по ключу
 *
 * @param head Указатель на голову списка
 * @param data Данные
 * @return const node_t* Найденный узел
 */
const list_t *list_search_by_key(const list_t *head, data_t *data, size_t *cmp)
{
    if (head == NULL || data == NULL)
        return NULL;

    if (cmp)
        (*cmp) = 0;
    const list_t *temp = head;
    while (temp != NULL)
    {
        if (cmp)
            (*cmp)++;
        if (temp->data->value == data->value)
            return temp;
        temp = temp->next;
    }

    return NULL;
}

/**
 * @brief Удаляет в односвязном списке узел по ключу
 *
 * @param head Указатель на голову списка
 * @param data Данные
 * @return int Код ошибки
 */
int list_remove_by_key(list_t **head, data_t *data)
{
    if (*head == NULL || data == NULL)
        return ERR_HEAD;

    if ((*head)->data->value == data->value)
    {
        list_t *next = (*head)->next;
        free(*head);
        *head = next;

        return ERR_OK;
    }

    list_t *temp = *head;
    list_t *prev = *head;
    while (temp != NULL)
    {
        if (temp->data->value == data->value)
        {
            list_t *next = temp->next;
            free(temp->data);
            free(temp);
            prev->next = next;
            return ERR_OK;
        }
        prev = temp;
        temp = temp->next;
    }

    return WARNING_ELEMENT_NOT_FOUND;
}

size_t list_size(const list_t *head)
{
    const list_t *tmp = head;
    size_t cnt = 0;
    while (tmp != NULL)
    {
        cnt++;
        tmp = tmp->next;
    }

    return cnt;
}

void list_print(const list_t *list)
{
    const list_t *temp = list;
    while (temp)
    {
        printf("[%c] -> ", temp->data->value);
        temp = temp->next;
    }

    printf("[NULL]");
}
