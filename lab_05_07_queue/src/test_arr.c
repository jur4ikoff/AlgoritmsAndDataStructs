#include "arr_queue.h"
#include "list_queue.h"
#include "errors.h"
#include "menu.h"
#include "constants.h"

int arr_test(void)
{
    int rc = ERR_OK;
    size_t itteration_count = 0;
    test_operations_t test_operation = TEST_INIT;
    arr_queue_t queue = {0};
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
            printf(">Выберите элемент для вставки: ");
            char element = getchar();
            if ((rc = arr_queue_push(&queue, element)) != ERR_OK)
            {
                printf("%sПереполнение очереди%s\n", YELLOW, RESET);
            }
            else
                printf("%sУспешное добавление в очередь элемента: %c%s\n", GREEN, element, RESET);
            // Добавлене элемента в очередь
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
                printf("%sУспешное удаление из очереди элемента: %c%s\n", GREEN, element, RESET);
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
    list_queue_t queue = {0};
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
            printf(">Выберите элемент для вставки: ");
            char element = getchar();
            if ((rc = list_queue_push(&queue, element)) != ERR_OK)
            {
                printf("%sПереполнение очереди%s\n", YELLOW, RESET);
            }
            else
                printf("%sУспешное добавление в очередь элемента: %c%s\n", GREEN, element, RESET);
            // Добавлене элемента в очередь
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
                printf("%sУспешное удаление из очереди элемента: %c%s\n", GREEN, element, RESET);
        }

        itteration_count++;
    }

    return ERR_OK;
}
