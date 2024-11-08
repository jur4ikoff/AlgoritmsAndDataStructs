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

#include "list_stack.h"
#include "static_stack.h"
#include <errors.h>
#include <stdio.h>
#include <string.h>

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

int input_string(char *string, size_t len)
{
    if (!fgets(string, len, stdin))
        return ERR_STRING;

    char *newline = strchr(string, '\n');
    if (!newline)
        return ERR_STRING_OVERFLOW;

    *newline = 0;
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
    printf("%s", RED);
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
        case ERR_STRING:
            printf("Ошибка при вводе строки\n");
            break;
        case ERR_STRING_OVERFLOW:
            printf("Переполнение стоки\n");
            break;
        case ERR_MEMORY_ALLOCATION:
            printf("Ошибка при выделении памяти\n");
            break;
    }
    printf("%s", RESET);
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
    list_stack_t list_stack = { 0 };

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
            printf("В этом режие можно определить является ли строка палиндромом\n");
            printf(">Введите строку для определения: ");
            char string[MAX_STRING_SIZE];
            fgetc(stdin);
            if ((rc = input_string(string, MAX_STRING_SIZE)) != ERR_OK)
                goto all_exit;

            if (static_stack_is_palindrome(string) == 0)
                printf("Строка не паллиндром\n");
            else
                printf("Строка паллиндром\n");
        }
        else if (operation == OP_TEST_STATIC)
        {
            printf("\nВ этом режиме можно протестировать функции для работы со стеком на основе массива\n"
                   "0 - Выход\n"
                   "1 - Вывод на экран\n"
                   "2 - Добавление элемента\n"
                   "3 - Удаление элемента\n");

            test_operations_t test_choose_operation = 1;

            static_stack_t static_stack;
            static_stack_init(&static_stack);

            while (test_choose_operation != TEST_EXIT)
            {
                if ((rc = input_test_operation(&test_choose_operation)) != ERR_OK)
                    goto all_exit;

                if (test_choose_operation == TEST_PRINT)
                {
                    static_stack_print(static_stack);
                }
                else if (test_choose_operation == TEST_ADD)
                {
                    printf(">Введите символ для добавления: ");
                    fgetc(stdin);
                    char el_to_add = getchar();
                    printf("%c\n", el_to_add);
                    if ((rc = static_stack_push(&static_stack, el_to_add)) != ERR_OK)
                        goto all_exit;
                    printf("%sСимвол добавлен%s\n", GREEN, RESET);
                    printf("КОЛИЧЕСТВО ЭЛЕМЕНТОВ %d\n", static_stack.top);
                }
                else if (test_choose_operation == TEST_POP)
                {
                    printf(">Удаление последнего символа\n");
                    char element = static_stack_pop(&static_stack, &rc);
                    if (rc != ERR_OK)
                        printf("%sПопытка удаления из пустого стека%s\n", YELLOW, RESET);
                    else
                        printf("%sУдален элемент %c%s\n", GREEN, element, RESET);
                }
                else
                {
                    rc = ERR_OPERATION;
                    goto all_exit;
                }
            }
        }

        else if (operation == OP_TEST_LIST)
        {
            char el_1 = 'a', el_2 = 'b', el_3 = 'c';
            list_stack_init(&list_stack);
            if ((rc = list_stack_push(&list_stack, &el_1, sizeof(el_1))) != ERR_OK)
            {
                goto all_exit;
            }
            if ((rc = list_stack_push(&list_stack, &el_2, sizeof(el_2))) != ERR_OK)
            {
                goto all_exit;
            }
            if ((rc = list_stack_push(&list_stack, &el_3, sizeof(el_3))) != ERR_OK)
            {
                goto all_exit;
            }
            list_stack_print_char(list_stack);
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

    list_stack_free(&list_stack);
    return rc;
}
