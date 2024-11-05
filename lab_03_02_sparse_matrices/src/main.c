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

/* Чтобы заполнить путь к файлам с матрицей самостоятельно, нужно запустить программу с флагом --manual (./app.exe --manual)*/

#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "errors.h"
#include "constants.h"
#include "utils.h"
#include "default_matrix.h"
#include "csc_matrix.h"
#include "time_measuring.h"

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
    printf("0 - Выход\n"
           "1 - Заполнить матрицы вручную\n"
           "2 - Заполнить матрицы рандомно\n"
           "3 - Вывести матрицы\n"
           "4 - Вывести матрицы в формате CSC\n"
           "5 - Сложить матрицы в обычном виде\n"
           "6 - Сложить матрицы в формате CSC\n"
           "7 - Сравнить эффективность\n"
           "8 - Справочная информация\n");
}

int input_operation(menu_t *operation)
{
    int input, rc = ERR_OK;
    if ((rc = input_integer(&input, ">>Введите номер операции: ", 0, MAX_OPERATION)) != ERR_OK)
    {
        if (rc == ERR_INPUT_INTEGER_NUMBER_RANGE)
            rc = ERR_RANGE_OPERATION;
        return rc;
    }

    *operation = (menu_t)input;
    return rc;
}

void help(void)
{
    printf("Программа для сложения разреженных матриц в обычном виде, и в формате csc\n"
           "Для того чтобы заполнить две матрицы вручную, нужно ввести путь к двум файлам следующей структуры:\n"
           "На первой строке количество строк и столбцов\n"
           "На последующих строках находится целочисленная матрица\n\n"
           "Для удобного вывода, записывайте числа, длинной не больше 4 знаков\n");
}

int main(int argc, char **argv)
{
    int rc = ERR_OK;
    print_menu();
    char filename_first[MAX_PATH_SIZE + 1], filename_second[MAX_PATH_SIZE + 1];
    matrix_t matrix_1 = {0}, matrix_2 = {0}, def_res = {0};
    csc_t csc_1 = {0}, csc_2 = {0}, csc_res = {0};
    FILE *file_1 = NULL, *file_2 = NULL;
    bool is_manual = false;

    if (argc == 2 && strcmp(argv[1], "--manual") == 0)
    {
        is_manual = true;
    }

    while (true)
    {
        menu_t operation;
        if ((rc = input_operation(&operation)) != ERR_OK)
            break;

        if (operation == MENU_EXIT)
        {
            printf("Успешное завершение работы программы\n");
            break;
        }
        else if (operation == MENU_FILL_MANUAL)
        {
            // Заполнение матриц вручную
            int n, m;
            // Ввод имени файла для первого файла
            if (is_manual)
            {
                if ((rc = input_string(filename_first, MAX_PATH_SIZE, ">>Введите путь к файлу с первой матрицей: ")) != ERR_OK)
                    break;
            }
            else
            {
                strcpy(filename_first, "matrix_1.txt");
            }

            int format;
            input_integer(&format, ">В каком формате входные данные?\n1 - Обычный\n2 - Координатный\n", 1, 2);
            file_1 = fopen(filename_first, "r");
            if (file_1 == NULL)
                break;

            if ((rc = get_matrix_info(file_1, &n, &m)) != ERR_OK)
            {
                fclose(file_1);
                break;
            }

            if ((rc = create_default_matrix(&matrix_1, n, m)) != ERR_OK)
            {
                fclose(file_1);
                break;
            }

            if (format == 1)
            {
                if ((rc = fill_default_matrix_from_file(file_1, &matrix_1)) != ERR_OK)
                {
                    fclose(file_1);
                    break;
                }
            }
            else if (format == 2)
            {
                if ((rc = fill_coord_matrix_from_file(file_1, &matrix_1)) != ERR_OK)
                {
                    fclose(file_1);
                    break;
                }
            }
            fclose(file_1);
            printf(">>Матрица из файла %s успешно прочитана\n", filename_first);

            // Ввод имени файла для второго файла
            if (is_manual)
            {
                if ((rc = input_string(filename_second, MAX_PATH_SIZE, ">>Введите путь к файлу со второй матрицей: ")) != ERR_OK)
                    break;
            }
            else
                strcpy(filename_second, "matrix_2.txt");

            file_2 = fopen(filename_second, "r");
            if (file_2 == NULL)
                break;

            if ((rc = get_matrix_info(file_2, &n, &m)) != ERR_OK)
            {
                fclose(file_2);
                break;
            }

            if ((rc = create_default_matrix(&matrix_2, n, m)) != ERR_OK)
            {
                fclose(file_2);
                break;
            }

            if (format == 1)
            {
                if ((rc = fill_default_matrix_from_file(file_2, &matrix_2)) != ERR_OK)
                {
                    fclose(file_2);
                    break;
                }
            }
            else if (format == 2)
            {
                if ((rc = fill_coord_matrix_from_file(file_2, &matrix_2)) != ERR_OK)
                {
                    fclose(file_2);
                    break;
                }
            }

            fclose(file_2);
            printf(">>Матрица из файла %s успешно прочитана\n", filename_second);
        }
        else if (operation == MENU_FILL_RANDOM)
        {

            // size_t test_count = 0;
            /*for (size_t i = 0; i < 1000; i++)
            {
                if (random_chance(10))
                    test_count++;
            }*/
            // printf("%.2f\n", (double)test_count / 1000);

            // Заполнение матрицы рандомно
            if ((rc = random_fill_default_matrix(&matrix_1)) != ERR_OK)
                break;
            printf("Первая матрица успешно записана\n");

            if ((rc = random_fill_default_matrix(&matrix_2)) != ERR_OK)
                break;
            printf("Вторая матрица успешно записана\n");
        }
        else if (operation == MENU_PRINT_DEF)
        {
            // Вывод матрицы в обычном виде
            if (matrix_1.rows_count == 0 || matrix_1.columns_count == 0 || matrix_2.rows_count == 0 || matrix_2.columns_count == 0)
                printf("Матрицы не заполнены\n");
            else
            {
                printf("\n————————————————————————————————————————————————————————————————————————————\nВывод первой матрицы:\n");
                print_matrix(matrix_1);
                printf("\n————————————————————————————————————————————————————————————————————————————\nВывод второй матрицы:\n");
                print_matrix(matrix_2);
            }
        }
        else if (operation == MENU_PRINT_CSC)
        {
            // Вывод матрицы в формате csc
            if (matrix_1.rows_count == 0 || matrix_1.columns_count == 0 || matrix_2.rows_count == 0 || matrix_2.columns_count == 0)
                printf("Матрицы не заполнены\n");
            else
            {
                printf("\nПервая матрица\n");
                csc_1 = convert_to_csc(matrix_1);
                if (csc_1.rc != ERR_OK)
                {
                    rc = csc_1.rc;
                    break;
                }
                print_csc_matrix(csc_1);

                printf("\nВторая матрица\n");
                csc_2 = convert_to_csc(matrix_2);
                if (csc_2.rc != ERR_OK)
                {
                    rc = csc_2.rc;
                    break;
                }
                print_csc_matrix(csc_2);
            }
        }
        else if (operation == MENU_ADD_DEF)
        {
            // Сложение матриц в обычном виде
            if (matrix_1.rows_count == 0 || matrix_1.columns_count == 0 || matrix_2.rows_count == 0 || matrix_2.columns_count == 0)
                printf("Матрицы не заполнены\n");
            else
            {
                if ((rc = add_matrix_t(matrix_1, matrix_2, &def_res)) != ERR_OK)
                    break;

                printf("Вывод результата сложения\n");
                print_matrix(def_res);
            }
        }
        else if (operation == MENU_ADD_CSC)
        {
            // Сложение матриц в формате CSC
            if (matrix_1.rows_count == 0 || matrix_1.columns_count == 0 || matrix_2.rows_count == 0 || matrix_2.columns_count == 0)
                printf("Матрицы не заполнены\n");
            else
            {
                csc_1 = convert_to_csc(matrix_1);
                if (csc_1.rc != ERR_OK)
                {
                    rc = csc_1.rc;
                    break;
                }

                csc_2 = convert_to_csc(matrix_2);
                if (csc_2.rc != ERR_OK)
                {
                    rc = csc_2.rc;
                    break;
                }

                if ((rc = sum_csc_matrix(csc_1, csc_2, &csc_res)) != ERR_OK)
                    break;

                printf("Вывод матрицы\n");
                print_csc_matrix(csc_res);
            }
        }
        else if (operation == MENU_COMPARE_EFFICIENCY)
        {
            // Сравнение эффекта
            printf("Запуск сравнения двух алгоритмов:\n");
            if ((rc = run_profiling()) != ERR_OK)
                break;
        }
        else if (operation == MENU_HELP)
        {
            // Справочная информация
            help();
        }
    }

    free_default_matrix(&matrix_1);
    free_default_matrix(&matrix_2);
    free_default_matrix(&def_res);
    free_csc_matrix(&csc_1);
    free_csc_matrix(&csc_2);
    free_csc_matrix(&csc_res);
    print_error_message(rc);
    return rc;
}
