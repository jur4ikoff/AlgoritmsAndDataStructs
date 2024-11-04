/*
ЛР4 разработка структуры данныых - стек
Задание: используя стек, определить, является ли строка палиндромом

Требование к реализации
Задание из вариантов
а) статическим массивом
б) динамическим массивом
б) связным списком.
При реализации стека списком в вывод текущего состояния стека добавить просмотр адресов элементов стека и
создать СВОЙ список или массив свободных областей (адресов освобождаемых элементов) с выводом его на экран.

ЗАДАНИЕ ИЗ МЕТОДА
- добавление элемента в стек,
- удаление элемента из стека,
- вычисление (обработка данных);
- Нужно вывести на экран время выполнения программы при реализации стека списком и массивом, а также указать требуемый объем памяти.
- Необходимо так же выдать на экран список адресов освобождаемых элементов при удалении элементов стека.
*/

#include <errors.h>
#include <stdio.h>

typedef enum
{
    OP_EXIT,
    OP_TASK,
    OP_TEST_STATIC,
    OP_TEST_LIST,
    OP_EFFICIENCY,
    OP_COUNT

} operations_t;

typedef enum
{
    TEST_EXIT,
    TEST_PRINT,
    TEST_ADD,
    TEST_POP,
    TEST_PEEK,
    TEST_COUNT
} test_operations_t;

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

int input_test_operation(test_operations_t *operation)
{
    printf(">Выберите операцию: ");
    int buffer;
    if (scanf("%d", &buffer) != 1)
        return ERR_OPERATION;

    if (buffer < 0 || buffer >= TEST_COUNT)
        return ERR_OPERATION;

    *operation = (test_operations_t)buffer;
    return ERR_OK;
}

// Обработка ошибок
void print_error_message(int arg)
{
    switch (arg)
    {
        case ERR_OPERATION:
            printf("Выбрана неверная операция\n");
            break;
        case ERR_STATIC_STACK_OVERFLOW:
            printf("Переполнение статического стека\n");
            break;
        case ERR_STATIC_STACK_UNDERFLOW:
            printf("Ошибка, попытка удаление из пустого стека\n");
            break;
    }
}

void print_menu(void)
{
    printf("Программа для работы со стеком\n"
           "0 - Выход\n"
           "1 - Узнать является ли строка паллиндромом\n"
           "2 - Тестирование стека на статическом массиве\n"
           "3 - Тестирование стека на связном списке\n"
           "4 - Замерный эксперимент\n");
}

int main(void)
{
    int rc = 0;
    operations_t operation = (operations_t)1;

    print_menu();

    while (operation != OP_EXIT)
    {
        if ((rc = input_menu_operation(&operation)) != ERR_OK)
            goto all_exit;

        if (operation == OP_EXIT)
        {
            goto all_exit;
        }
        else if (operation == OP_TASK)
        {
            ;
        }
        else if (operation == OP_TEST_STATIC)
        {
            printf("\nВ этом режиме можно протестировать функции для работы со стеком на основе массива\n");
            printf("0 - Выход\n1 - Вывод на экран\n2 - Добавление элемента\n3 - Удаление элемента\n4 - Просмотр последнего элемента\n");
            printf(">Выберите операцию: ");
            test_operations_t test_choose_operation;
            if ((rc = input_test_operation(&test_choose_operation)) != ERR_OK)
                goto all_exit;
        }

        else if (operation == OP_TEST_LIST)
        {
            ;
        }
        else
        {
            rc = ERR_OPERATION;
            goto all_exit;
        }
    }
    all_exit:
    if (rc)
        print_error_message(rc);
    return rc;
}
