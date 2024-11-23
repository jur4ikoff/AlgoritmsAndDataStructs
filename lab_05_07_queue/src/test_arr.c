#include "arr_queue.h"
#include "constants.h"
#include "errors.h"
#include "list_queue.h"
#include "menu.h"
#include <stdlib.h>

int input_symbol(char *element)
{

    if (scanf(" %c", element) != 1)
        return ERR_SYMBOL_INPUT;

    if (getchar() != '\n')
        return ERR_SYMBOL_INPUT;

    return ERR_OK;
}

int arr_test(void)
{
    int rc = ERR_OK;
    size_t itteration_count = 0;
    test_operations_t test_operation = TEST_INIT;
    arr_queue_t queue = { 0 };

    arr_queue_init(&queue);

    while (test_operation != TEST_EXIT)
    {
        if (itteration_count % 3 == 0)
            print_test_menu();

        if ((rc = input_test_operation(&test_operation)) != ERR_OK)
            return rc;

        if (test_operation == TEST_EXIT)
        {
            printf("%sВыход из режима тестирования%s\n", GREEN, RESET);
            return rc;
        }
        else if (test_operation == TEST_PRINT)
        {
            arr_queue_print_char(queue);
        }
        else if (test_operation == TEST_ADD)
        {
            printf(">Выберите один символ для вставки: ");
            char element;
            if ((rc = input_symbol(&element)) != ERR_OK)
                return rc;

            if ((rc = arr_queue_push(&queue, element)) != ERR_OK)
            {
                printf("%sПереполнение очереди%s\n", YELLOW, RESET);
            }
            else
            {
                // Добавлене элемента в очередь
                printf("%ld\n", sizeof(data_t));
                printf("%sУспешное добавление в очередь элемента: %c%s\n", GREEN, element, RESET);
                printf("%sАдрес начала списка %p, адрес конца списка%p%s\n", GREEN, (void *)queue.start, (void *)queue.end, RESET);
            }
        }
        else if (test_operation == TEST_POP)
        {
            // Удаление из очереди
            char element;
            if ((rc = arr_queue_pop(&queue, &element)) != ERR_OK)
            {
                printf("%sПопытка удаления из пустой очереди%s\n", YELLOW, RESET);
            }
            else
            {
                printf("%sУспешное удаление из очереди элемента: %c %s\n", GREEN, element, RESET);
                printf("%sАдрес начала списка %p, адрес конца списка%p%s\n", GREEN, (void *)queue.start, (void *)queue.end, RESET);
            }
        }

        itteration_count++;
    }

    return ERR_OK;
}

int list_test(void)
{
    int rc = ERR_OK;
    size_t itteration_count = 0;
    test_operations_t test_operation = TEST_INIT;
    list_queue_t queue = { 0 };

    list_queue_init(&queue);

    while (test_operation != TEST_EXIT)
    {
        if (itteration_count % 3 == 0)
            print_test_menu();

        if ((rc = input_test_operation(&test_operation)) != ERR_OK)
            return rc;

        if (test_operation == TEST_EXIT)
        {
            printf("%sВыход из режима тестирования%s\n", GREEN, RESET);
            return rc;
        }
        else if (test_operation == TEST_PRINT)
        {
            // Вывод очереди на экран
            list_queue_print_char(queue);
        }
        else if (test_operation == TEST_ADD)
        {
            printf(">Выберите один символ для вставки: ");
            char element;
            if ((rc = input_symbol(&element)) != ERR_OK)
                return rc;

            if ((rc = list_queue_push(&queue, element)) != ERR_OK)
            {
                printf("%sПереполнение очереди%s\n", YELLOW, RESET);
            }
            else
            {
                // Добавлене элемента в очередь
                printf("%sУспешное добавление в очередь элемента: %c%s\n", GREEN, element, RESET);
                printf("%sАдрес начала списка %p, адрес конца списка %p%s\n", GREEN, (void *)queue.head, (void *)queue.end, RESET);
            }
        }
        else if (test_operation == TEST_POP)
        {
            // Удаление из очереди
            char element;
            if ((rc = list_queue_pop(&queue, &element)) != ERR_OK)
            {
                printf("%sПопытка удаления из пустой очереди%s\n", YELLOW, RESET);
            }
            else
            {
                
                printf("%sУспешное удаление из очереди элемента: %c%s\n", GREEN, element, RESET);
                printf("%sАдрес начала списка %p, адрес конца списка %p%s\n", GREEN, (void *)queue.head, (void *)queue.end, RESET);
            }
        }

        itteration_count++;
    }

    return ERR_OK;
}
