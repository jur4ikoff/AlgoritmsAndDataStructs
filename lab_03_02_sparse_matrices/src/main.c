/*
Вариант 2

Задание общее
Разработать программу умножения или сложения разреженных матриц.
Предусмотреть возможность ввода данных, как с клавиатуры, так и использования
заранее подготовленных данных. Матрицы хранятся и выводятся в форме трех
объектов. Для небольших матриц можно дополнительно вывести матрицу в виде
матрицы. Величина матриц - любая (допустим, 1000*1000). Сравнить эффективность
(по памяти и по времени выполнения) стандартных алгоритмов обработки матриц с
алгоритмами обработки разреженных матриц при различной степени разреженности
матриц и различной размерности матриц.

Задание из варианта
Разреженная (содержащая много нулей) матрица хранится в форме 3-х объектов
(CSC):
- вектор A содержит значения ненулевых элементов;
- вектор IA содержит номера строк для элементов вектора A;
- вектор JA, в элементе Nk которого находится номер компонент в A и IA, с
которых начинается описание столбца Nk матрицы A.

1. Смоделировать операцию сложения двух матриц, хранящихся в этой
форме, с получением результата в той же форме.
2. Произвести операцию сложения, применяя стандартный алгоритм
работы с матрицами.
3. Сравнить время выполнения операций и объем памяти при
использовании этих 2-х алгоритмов при различном проценте заполнения
матриц.
*/

/* Чтобы заполнить матрицы самостоятельно, нужно запустить программу с флагом --manual (./app.exe --manual),
Для того, чтобы программа работала без лишнего вывода, запустить с флагом --quite*/

#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "errors.h"
#include "constants.h"
#include "utils.h"
#include "default_matrix.h"

typedef enum
{
    MENU_EXIT,
    MENU_FILL_MANUAL,
    MENU_FILL_RANDOM,
    MENU_PRINT_DEF,
    MENU_PRINT_CSC,
    MENU_ADD_DEF,
    MENU_ADD_CSC,
    MENU_COMPARE_EFFICIENCY,
    MENU_HELP
} menu_t;

void print_menu(void)
{
    printf("\n"
           "0 - Выход\n"
           "1 - Заполнить матрицы вручную\n"
           "2 - Заполнить матрицы рандомно\n"
           "2 - Вывести матрицы\n"
           "3 - Вывести матрицы в формате CSC\n"
           "4 - Сложить матрицы в обычном виде\n"
           "5 - Сложить матрицы в формате CSC\n"
           "6 - Сравнить эффективность\n"
           "7 - Справочная информация\n");
}

int input_operation(menu_t *operation)
{
    printf("Введите номер операции: ");
    int input;
    if (scanf("%d", &input) != 1)
        return ERR_INPUT_OPERATION;
    fgetc(stdin);

    if (input < 0 || input > MAX_OPERATION)
        return ERR_RANGE_OPERATION;

    *operation = (menu_t)input;
    return ERR_OK;
}

void help(void)
{
    printf("Программа для сложения разреженных матриц в обычном виде, и в формате csc\n"
           "Для того чтобы заполнить две матрицы вручную, нужно ввести путь к двум файлам следующей структуры:\n"
           "На первой строке количество строк и столбцов\n"
           "На последующих строках находится целочисленная матрица\n\n");
}

int main(int argc, char **argv)
{
    int rc = ERR_OK;
    print_menu();
    char filename_first[MAX_PATH_SIZE + 1], filename_second[MAX_PATH_SIZE + 1];
    matrix_t matrix_1; // matrix_2;
    bool is_manual = false;
    if (argc == 2 && strcmp(argv[1], "--manual") == 0)
    {
        is_manual = true;
    }

    while (true)
    {
        menu_t operation;
        if ((rc = input_operation(&operation)) != ERR_OK)
        {
            print_error_message(rc);
            return rc;
        }

        switch (operation)
        {
        case MENU_EXIT:
            // Выход из программы
            printf("Успешное завершение работы программы\n");
            return rc;
        case MENU_FILL_MANUAL:
            // Заполнение матриц вручную
            // Ввод имени файла для первого файла
            if (is_manual)
            {
                if ((rc = input_string(filename_first, MAX_PATH_SIZE, "Введите путь к файлу с первой матрицей: ")) != ERR_OK)
                {
                    print_error_message(rc);
                    return rc;
                }
            }
            else
            {
                strcpy(filename_first, "matrix_1.txt");
            }

            FILE *file_first = fopen(filename_first, "r");
            if (file_first == NULL)
            {
                print_error_message(ERR_FILENAME);
                return ERR_FILENAME;
            }

            if ((rc = create_default_matrix(file_first, &matrix_1)) != ERR_OK)
            {
                print_error_message(rc);
                return rc;
            }

            if ((rc = fill_matrix(file_first, &matrix_1)) != ERR_OK)
            {
                print_error_message(rc);
                return rc;
            }
            print_matrix(matrix_1);

            free_matrix(&matrix_1); // УБРАТЬ НАХУЙ

            fclose(file_first);
            // Ввод имени файла для второго файла
            if ((rc = input_string(filename_second, MAX_PATH_SIZE, "Введите путь к файлу со второй матрицей: ")) != ERR_OK)
            {
                print_error_message(rc);
                return rc;
            }

            // заполнение матрицы из файла

            break;

        case MENU_FILL_RANDOM:
            // Заполнение матрицы рандомно
            break;

        case MENU_PRINT_DEF:
            // Вывод матрицы в обычном виде
            break;

        case MENU_PRINT_CSC:
            // Вывод матрицы в формате CSC
            break;

        case MENU_ADD_DEF:
            // Сложение матриц в обычном виде
            break;

        case MENU_ADD_CSC:
            // Сложение матриц в формате CSC
            break;

        case MENU_COMPARE_EFFICIENCY:
            // Сравнение эффект
            break;
        case MENU_HELP:
            // Справочная информация
            help();
            break;
        }
    }

    return rc;
}
