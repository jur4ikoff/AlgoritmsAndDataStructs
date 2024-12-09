#include "menu.h"
#include "constants.h"
#include "errors.h"
#include "simulation.h"
#include <stdio.h>

// Ввод операции для меню
int input_menu_operation(operations_t *operation)
{
    printf(">Выберите операцию: ");
    int buffer;
    if (scanf("%d", &buffer) != 1)
        return ERR_OPERATION;

    if (buffer < 0 || buffer >= OP_COUNT)
        return ERR_OPERATION;

    *operation = (operations_t)buffer;
    return ERR_OK;
}

// Вывод информации о программе
void print_guide(void)
{
    printf("Лабораторная работа по теме \"тип данных: очередь\",\n"
           "представленном в виде массива и односвязного списка.\n");
}

// Вывод сообщения об ошибке
void print_error_message(int arg)
{
    printf("%s", RED);
    switch (arg)
    {
        case ERR_OPERATION:
            printf("Выбрана неверная операция\n");
            break;
        case ERR_QUEUE_OVERFLOW:
            printf("Очередь переполнена\n");
            break;
        case ERR_QUEUE_UNDERFLOW:
            printf("Удаление из пустой очереди\n");
            break;
        case ERR_MEMORY_ALLOCATION:
            printf("Ошибка при выделении памяти\n");
            break;
        case ERR_DATA:
            printf("Ошибка при создании нового элемента\n");
            break;
        case ERR_SYMBOL_INPUT:
            printf("Ошибка при вводе символа\n");
            break;
        case ERR_SIMULATION_PARAM:
            printf("Неверный ввод параметров симуляции\n");
            break;
    }
    printf("%s", RESET);
}

// Ввод теестовой операции
int input_test_operation(test_operations_t *operation)
{
    printf(">Выберите тестовую операцию: ");
    int buffer;
    if (scanf("%d", &buffer) != 1)
        return ERR_OPERATION;

    if (buffer < 0 || buffer >= TEST_COUNT)
    {
        *operation = TEST_UNKNOWN;
        return ERR_OK;
    }
    *operation = (test_operations_t)buffer;
    fgetc(stdin);
    return ERR_OK;
}

// Вывод меню
void print_menu(void)
{
    printf("0 - Выход\n"
           "1 - Тестирование очереди на статическом массиве\n"
           "2 - Тестирование очереди на списке\n"
           "3 - Симуляция работы\n"
           "4 - Изменить параметры симуляции\n");
}

// Вывод меню для тестирования очередей
void print_test_menu(void)
{
    printf("\nВ этом режиме можно протестировать работу с очередью\n"
           "0 - Выход\n"
           "1 - Вывод всей очереди на экран\n"
           "2 - Добавление элемента\n"
           "3 - Удаление элемента\n");
}

// Функция редактирования параметров симуляции
int edit_params(void)
{
    int t1_low, t1_high;
    int t2_low, t2_high;
    size_t epx_count;
    printf("Введите минимум и максимум T1 (изначально 0, 6): ");
    if (scanf("%d%d", &t1_low, &t1_high) != 2)
        return ERR_SIMULATION_PARAM;

    printf("Введите минимум и максимум T2 (изначально 0, 1): ");
    if (scanf("%d%d", &t2_low, &t2_high) != 2)
        return ERR_SIMULATION_PARAM;

    printf("Введите максимальное число заявок (изначально 1000): ");
    if (scanf("%zu", &epx_count) != 1)
        return ERR_SIMULATION_PARAM;

    T1_LOWER = t1_low;
    T1_UPPER = t1_high;
    T2_LOWER = t2_low;
    T2_UPPER = t2_high;
    MAX_REQUEST_COUNT = epx_count;
    return ERR_OK;
}
