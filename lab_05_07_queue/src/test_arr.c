#include "arr_queue.h"
#include "constants.h"
#include "errors.h"
#include "list_queue.h"
#include "menu.h"
#include <stdlib.h>
#include <time.h>

/**
 * @brief Ввод символа в структуру
 * @param elememt Указатель на переменную типа data_t
 * @return Код возврата
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

// Тестирования очереди на статическом массиве
int arr_test(void)
{
    // Инициализация
    int rc = ERR_OK;
    size_t itteration_count = 0;
    test_operations_t test_operation = TEST_INIT;
    arr_queue_t queue = {0};
    struct timespec start, end;
    double time;
    // Инициализация очереди
    arr_queue_init(&queue);

    while (test_operation != TEST_EXIT)
    {
        // Раз в 3 запуска, выводится меню
        if (itteration_count % 3 == 0)
            print_test_menu();

        // Получаем операцию
        if ((rc = input_test_operation(&test_operation)) != ERR_OK)
            return rc;

        if (test_operation == TEST_EXIT)
        {
            // Выход из режима
            printf("%sВыход из режима тестирования%s\n", GREEN, RESET);
            return rc;
        }
        else if (test_operation == TEST_PRINT)
        {

            // Вывод очереди на экран
            arr_queue_print_char(queue);
        }
        else if (test_operation == TEST_ADD)
        {
            // Добавление элемента для очереди
            printf(">Выберите один символ для вставки: ");
            data_t data;
            // Ввод символа
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
                // Добавление элемента в очередь и замер времени
                clock_gettime(CLOCK_MONOTONIC_RAW, &end);
                time = (end.tv_sec - start.tv_sec) * 1e6 + (end.tv_nsec - start.tv_nsec) / 1e3;
                printf("%sУспешное добавление в очередь элемента: %c%s\n", GREEN, data.element, RESET);
                printf("%sАдрес начала списка %p, адрес конца списка%p Время добавления %.2f мкс%s\n", GREEN, (void *)queue.start, (void *)queue.end, time, RESET);
            }
        }
        else if (test_operation == TEST_POP)
        {
            // Удаление элемента из очереди
            data_t data;
            clock_gettime(CLOCK_MONOTONIC_RAW, &start);
            if ((rc = arr_queue_pop(&queue, &data)) != ERR_OK)
            {
                printf("%sПопытка удаления из пустой очереди%s\n", YELLOW, RESET);
                clock_gettime(CLOCK_MONOTONIC_RAW, &end);
            }
            else
            {
                // Замер времени
                clock_gettime(CLOCK_MONOTONIC_RAW, &end);
                time = (end.tv_sec - start.tv_sec) * 1e6 + (end.tv_nsec - start.tv_nsec) / 1e3;
                printf("%sУспешное удаление из очереди элемента: %c %s\n", GREEN, data.element, RESET);
                printf("%sАдрес начала списка %p, адрес конца списка %p Время удаления %.2f мкс%s\n", GREEN, (void *)queue.start, (void *)queue.end, time, RESET);
            }
        }
        else if (test_operation == TEST_UNKNOWN)
        {
            // Операция неизвестна
            printf("%sНеизвестная операция%s\n", YELLOW, RESET);
        }

        itteration_count++;
    }

    return ERR_OK;
}

// Тестирование очереди на односвязном списке
int list_test(void)
{
    // Инициализация переменных
    int rc = ERR_OK;
    size_t itteration_count = 0;
    test_operations_t test_operation = TEST_INIT;
    list_queue_t queue = {0};
    struct timespec start, end;
    double time;
    list_queue_init(&queue);

    while (test_operation != TEST_EXIT)
    {
        // Вывод меню раз в 3 прогона
        if (itteration_count % 3 == 0)
            print_test_menu();

        // Получение операции
        if ((rc = input_test_operation(&test_operation)) != ERR_OK)
        {
            list_queue_free(&queue);
            return rc;
        }

        if (test_operation == TEST_EXIT)
        {
            // Выход из режима тестирования
            printf("%sВыход из режима тестирования%s\n", GREEN, RESET);
            list_queue_free(&queue);
            return rc;
        }
        else if (test_operation == TEST_PRINT)
        {
            // Вывод очереди на экран
            list_queue_print_char(queue);
        }
        else if (test_operation == TEST_ADD)
        {
            // Добавление элемента в очередь
            printf(">Выберите один символ для вставки: ");
            data_t data;
            // Ввод элемента
            if ((rc = input_symbol_to_data(&data)) != ERR_OK)
            {
                print_error_message(rc);
                list_queue_free(&queue);
                return rc;
            }
            // Запуск времени
            clock_gettime(CLOCK_MONOTONIC_RAW, &start);
            // Добавление в список
            if ((rc = list_queue_push(&queue, &data, sizeof(data_t))) != ERR_OK)
            {
                printf("%sПереполнение очереди%s\n", YELLOW, RESET);
                clock_gettime(CLOCK_MONOTONIC_RAW, &end);
            }
            else
            {
                // Окончание замера и вывод сообщения об успехе
                clock_gettime(CLOCK_MONOTONIC_RAW, &end);
                time = (end.tv_sec - start.tv_sec) * 1e6 + (end.tv_nsec - start.tv_nsec) / 1e3;
                printf("%sУспешное добавление в очередь элемента: %c%s\n", GREEN, data.element, RESET);
                printf("%sАдрес начала списка %p, адрес конца списка %p Время добавления %.2f мкс%s\n", GREEN, (void *)queue.head, (void *)queue.end, time, RESET);
            }
        }
        else if (test_operation == TEST_POP)
        {
            // Удаление элемента из очереди
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
                // Вывод сообщения об успехе
                time = (end.tv_sec - start.tv_sec) * 1e6 + (end.tv_nsec - start.tv_nsec) / 1e3;
                printf("%sУспешное удаление из очереди элемента: %c %s\n", GREEN, data.element, RESET);
                printf("%sАдрес начала списка %p, адрес конца списка%p Время удаления %.2f мкс%s\n", GREEN, (void *)queue.head, (void *)queue.end, time, RESET);
            }
        }
        else if (test_operation == TEST_UNKNOWN)
        {
            // Операция неизвестна
            printf("%sНеизвестная операция%s\n", YELLOW, RESET);
        }
        itteration_count++;
    }

    // Освобождение памяти и возврат результата
    list_queue_free(&queue);
    return ERR_OK;
}
