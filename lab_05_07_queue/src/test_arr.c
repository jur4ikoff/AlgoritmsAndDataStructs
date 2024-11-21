#include "arr_queue.h"
#include "errors.h"
#include "menu.h"

void arr_queue_print_char(const arr_queue_t queue)
{
    if (queue.count == 0)
    {
        printf("%sОчередь пустая%s\n", YELLOW, RESET);
        return;
    }
    for (size_t i = 0; i < queue.count; i++)
    {
        printf("%c ", queue.data->element);
    }
    printf("\n");
}

void arr_test(void)
{
    int rc = ERR_OK;
    size_t itteration_count = 0;
    test_operations_t test_operation = TEST_INIT;

    while (test_operation != TEST_EXIT)
    {
        if (itteration_count % 3 == 0)
            print_test_menu();

        if ((rc = input_test_operation(&test_operation)) != ERR_OK)
        {
            printf("%sВыбрана неверная операция, выход в главное меню%s\n", YELLOW, RESET);
            return;
        }
        printf("%d\n", test_operation);

        if (test_operation == TEST_EXIT)
        {
            printf("%sВыход из режима тестирования%s\n", GREEN, RESET);
            return;
        }
        else if (test_operation == TEST_PRINT)
        {
            // print queque
        }
        else if (test_operation == TEST_ADD)
        {
            // Добавлене элемента в очередь
        }
        else if (test_operation == TEST_POP)
        {
            // Удаление из очереди
        }

        itteration_count++;
    }
}
