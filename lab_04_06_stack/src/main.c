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
    OP_TEST_DYNAMIC,
    OP_TEST_LIST,
    OP_EFFICIENCY,
    OP_COUNT

} operations_t;

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

// Обработка ошибок
void print_error_message(int arg)
{
    switch (arg)
    {
        case ERR_OPERATION:
            printf("Выбрана неверная операция\n");
            break;
    }
}

void print_menu(void)
{
    printf("Программа для работы со стеком\n"
           "0 - Выход"
           "1 - Узнать является ли строка паллиндромом\n"
           "2 - Всякая всячина с стеком на статическом массиве\n"
           "3 - Всякая всячина с стеком на динамическом массиве\n",
           "4 - Всякая всячина с стеком на связном списке\n"
           "5 - Замерный эксперимент\n");
}

int main(void)
{
    int rc = 0;
    operations_t operation = (operations_t)1;

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
            ;
        }
        else if (operation == OP_TEST_DYNAMIC)
        {
            ;
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
