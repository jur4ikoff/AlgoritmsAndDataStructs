#include "menu.h"
#include "errors.h"
#include "constants.h"
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

/*int input_string(char *string, size_t len)
{
    if (!fgets(string, len, stdin))
        return ERR_STRING;

    if (strlen(string) < 1)
        return ERR_STRING;

    char *newline = strchr(string, '\n');
    if (!newline)
        return ERR_STRING_OVERFLOW;

    *newline = 0;
    return ERR_OK;
}*/

// Обработка ошибок
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
