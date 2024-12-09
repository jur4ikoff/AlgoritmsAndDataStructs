/*
## Задание:
Построить дерево в соответствии со своим вариантом задания.
Вывести его на экран в виде дерева. Реализовать основные операции
работы с деревом: обход дерева, включение, исключение и поиск узлов.
Сравнить эффективность алгоритмов сортировки и поиска в зависимости от высоты деревьев и степени их ветвления.

## Вариант
Построить двоичное дерево поиска из букв вводимой строки. Вывести его на экран в виде
дерева. Выделить цветом все буквы, встречающиеся более одного раза. Удалить из дерева эти
буквы. Вывести оставшиеся элементы дерева при постфиксном его обходе. Сравнить время
удаления повторяющихся букв из дерева и из строки.
*/

#include <stdio.h>
#include "errors.h"
#include "constants.h"
#include <string.h>
#include "menu.h"
#include <stdlib.h>
#include "binary_tree.h"
#include "test.h"

/**
 * @brief Функция для записи строки в переменную. Функция автоматически выделяет память под строку
 * @param string Указатель на строку
 * @param file Указатель на файловую переменную
 * @return Код возврата
 */
int input_line(char **string, FILE *file)
{
    ssize_t read = 0;
    size_t len = 0;

    if ((read = getline(string, &len, file)) == -1)
        return ERR_STRING;

    if (read > MAX_STRING_LEN)
        return ERR_STRING;

    char *newline = strchr(*string, '\n');
    if (!newline)
        return ERR_STRING;

    *newline = 0;
    return ERR_OK;
}

int main(void)
{
    print_info();
    int rc = ERR_OK;
    char *string = NULL;
    operations_t operation = OP_COUNT;
    int itteration_count = 0;
    int is_string = 0;
    // int is_tree = 0;
    //  tree_t *tree = NULL;
    while (operation != OP_EXIT && rc == ERR_OK)
    {
        // Раз в 3 запроса выводим меню
        if (itteration_count % 3 == 0)
            print_menu();
        itteration_count++;

        // Принимаем операцию
        printf(">>Введите операцию: ");
        operation = input_operation();

        if (operation == OP_EXIT)
        {
            // Выход из программы
            printf("%sВыход из программы%s\n", GREEN, RESET);
            goto exit;
        }
        else if (operation == OP_TREE_TEST)
        {
            // тестирование дерева
            // Запуск подпрограммы для тестирования дерева
            test_binary_tree();
            itteration_count = 0;
        }
        /*else if (operation == OP_INPUT_STRING)
         {
             if ((rc = input_line(&string, stdin)) != ERR_OK)
             {
                 print_error_message(rc);
                 return rc;
             }
             is_string = 1;
         }
         else if (operation == OP_BUILD_TREE)
         {
             tree = tree_create();
             if (!tree)
             {
                 rc = ERR_MEMORY_ALLOCATION;
                 goto exit;
             }
             ;
         }*/
        if (operation == OP_UNKNOWN)
        {
            printf("%sВыбрана неверная операция%s\n", YELLOW, RESET);
        }
    }

    (void)is_string;
    //(void)is_tree;
    goto exit;

exit:
    if (rc)
        print_error_message(rc);
    free(string);
    // tree_free(tree);
    return rc;
}
