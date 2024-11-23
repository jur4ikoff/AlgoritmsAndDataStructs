#include "menu.h"
#include "constants.h"
#include "errors.h"
#include <stdio.h>

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
    }
    printf("%s", RESET);
}

int input_test_operation(test_operations_t *operation)
{
    printf(">Выберите тестовую операцию: ");
    int buffer;
    if (scanf("%d", &buffer) != 1)
        return ERR_OPERATION;

    if (buffer < 0 || buffer >= TEST_COUNT)
        return ERR_OPERATION;
    *operation = (test_operations_t)buffer;
    fgetc(stdin);
    return ERR_OK;
}

void print_menu(void)
{
    printf("0 - Выход\n"
           "1 - Тестирование очереди на статическом массиве\n"
           "2 - Тестирование очереди на списке\n"
           "3 - Симуляция работы\n"
           "4 - Замерный эксперимент\n");
}

void print_test_menu(void)
{
    printf("\nВ этом режиме можно протестировать работу с очередью\n"
           "0 - Выход\n"
           "1 - Вывод всей очереди на экран\n"
           "2 - Добавление элемента\n"
           "3 - Удаление элемента\n");
}
