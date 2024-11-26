#include "arr_queue.h"
#include "constants.h"
#include "errors.h"
#include "list_queue.h"
#include "menu.h"
#include <stdlib.h>
#include <time.h>

/**
 * @brief Ввод символа в структуру
 */
int input_symbol_to_data(data_t *element)
{

    char el;
    if (scanf("%c", &el) != 1)
        return ERR_SYMBOL_INPUT;

    if (getchar() != '\n')
        return ERR_SYMBOL_INPUT;

    element->element = el;
    return ERR_OK;
}

int arr_test(void)
{
    int rc = ERR_OK;
    size_t itteration_count = 0;
    test_operations_t test_operation = TEST_INIT;
    arr_queue_t queue = { 0 };
    struct timespec start, end;
    double time;

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
            data_t data;
            if ((rc = input_symbol_to_data(&data)) != ERR_OK)
            {
                print_error_message(rc);
                return rc;
            }
            clock_gettime(CLOCK_MONOTONIC_RAW, &start);
            if ((rc = arr_queue_push(&queue, &data)) != ERR_OK)
            {
                printf("%sПереполнение очереди%s\n", YELLOW, RESET);
                clock_gettime(CLOCK_MONOTONIC_RAW, &end);
            }
            else
            {
                // Добавление элемента в очередь
                clock_gettime(CLOCK_MONOTONIC_RAW, &end);
                time = (end.tv_sec - start.tv_sec) * 1e6 + (end.tv_nsec - start.tv_nsec) / 1e3;
                printf("%sУспешное добавление в очередь элемента: %c%s\n", GREEN, data.element, RESET);
                printf("%sАдрес начала списка %p, адрес конца списка%p Время добавления %.2f мкс%s\n", GREEN, (void *)queue.start, (void *)queue.end, time, RESET);
            }
        }
        else if (test_operation == TEST_POP)
        {
            // Удаление из очереди
            data_t data;
            clock_gettime(CLOCK_MONOTONIC_RAW, &start);
            if ((rc = arr_queue_pop(&queue, &data)) != ERR_OK)
            {
                printf("%sПопытка удаления из пустой очереди%s\n", YELLOW, RESET);
                clock_gettime(CLOCK_MONOTONIC_RAW, &end);
            }
            else
            {
                clock_gettime(CLOCK_MONOTONIC_RAW, &end);
                time = (end.tv_sec - start.tv_sec) * 1e6 + (end.tv_nsec - start.tv_nsec) / 1e3;
                printf("%sУспешное удаление из очереди элемента: %c %s\n", GREEN, data.element, RESET);
                printf("%sАдрес начала списка %p, адрес конца списка %p Время удаления %.2f мкс%s\n", GREEN, (void *)queue.start, (void *)queue.end, time, RESET);
            }
        }
        else if (test_operation == TEST_UNKNOWN)
        {
            printf("%sНеизвестная операция%s\n", YELLOW, RESET);
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
    struct timespec start, end;
    double time;
    list_queue_init(&queue);

    while (test_operation != TEST_EXIT)
    {
        if (itteration_count % 3 == 0)
            print_test_menu();

        if ((rc = input_test_operation(&test_operation)) != ERR_OK)
        {
            list_queue_free(&queue);
            return rc;
        }

        if (test_operation == TEST_EXIT)
        {
            printf("%sВыход из режима тестирования%s\n", GREEN, RESET);
            list_queue_free(&queue);
            return rc;
        }
        else if (test_operation == TEST_PRINT)
        {
            list_queue_print_char(queue);
        }
        else if (test_operation == TEST_ADD)
        {
            printf(">Выберите один символ для вставки: ");
            data_t data;
            if ((rc = input_symbol_to_data(&data)) != ERR_OK)
            {
                print_error_message(rc);
                list_queue_free(&queue);
                return rc;
            }
            clock_gettime(CLOCK_MONOTONIC_RAW, &start);
            if ((rc = list_queue_push(&queue, &data, sizeof(data))) != ERR_OK)
            {
                printf("%sПереполнение очереди%s\n", YELLOW, RESET);
                clock_gettime(CLOCK_MONOTONIC_RAW, &end);
            }
            else
            {
                // Добавление элемента в очередь
                clock_gettime(CLOCK_MONOTONIC_RAW, &end);
                time = (end.tv_sec - start.tv_sec) * 1e6 + (end.tv_nsec - start.tv_nsec) / 1e3;
                printf("%sУспешное добавление в очередь элемента: %c%s\n", GREEN, data.element, RESET);
                printf("%sАдрес начала списка %p, адрес конца списка %p Время добавления %.2f мкс%s\n", GREEN, (void *)queue.head, (void *)queue.end, time, RESET);
            }
        }
        else if (test_operation == TEST_POP)
        {
            // Удаление из очереди
            data_t data;
            clock_gettime(CLOCK_MONOTONIC_RAW, &start);
            if ((rc = list_queue_pop(&queue, &data, sizeof(data))) != ERR_OK)
            {
                printf("%sПопытка удаления из пустой очереди%s\n", YELLOW, RESET);
                clock_gettime(CLOCK_MONOTONIC_RAW, &end);
            }
            else
            {
                clock_gettime(CLOCK_MONOTONIC_RAW, &end);
                time = (end.tv_sec - start.tv_sec) * 1e6 + (end.tv_nsec - start.tv_nsec) / 1e3;
                printf("%sУспешное удаление из очереди элемента: %c %s\n", GREEN, data.element, RESET);
                printf("%sАдрес начала списка %p, адрес конца списка%p Время удаления %.2f мкс%s\n", GREEN, (void *)queue.head, (void *)queue.end, time, RESET);
            }
        }
        else if (test_operation == TEST_UNKNOWN)
        {
            printf("%sНеизвестная операция%s\n", YELLOW, RESET);
        }

        itteration_count++;
    }

    list_queue_free(&queue);
    return ERR_OK;
}
