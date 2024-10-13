#include "database_operations.h"
#include <stdio.h>
#include "errors.h"
#include "constants.h"
#include <string.h>
#include "student_operations.h"
#include "utils.h"

int database_open(FILE **file, char *filename, char *mode)
{
    *file = fopen(filename, mode);

    if (*file == NULL)
        return ERR_FILENAME;

    return ERR_OK;
}

int database_choose_name(char *string)
{
    FILE *file;
    int rc;

    if (strlen(string) > MAX_PATH_LEN)
        return ERR_STRING_OVERFLOW;

    // Проверка файла на существование
    if ((rc = database_open(&file, string, "r")) != ERR_OK)
        return rc;
    fclose(file);

    return ERR_OK;
}

int database_import_students(FILE *file, students_t *students, size_t *count)
{
    rewind(file);
    *count = 0;
    int rc = ERR_OK;
    while (rc != END_OF_FILE)
    {
        if ((rc = student_input(file, students, *count)) == ERR_OK)
        {
            (*count)++;
            if (*count > MAX_STUDENTS_COUNT)
                return ERR_TOO_MANY_STUDENTS;
        }
        else if (rc == END_OF_FILE)
            return ERR_OK;
        else
            return rc;
    }

    return rc;
}

int database_save(char *filename, students_t *students, size_t count)
{
    FILE *file;
    int rc = ERR_OK;
    if ((rc = database_open(&file, filename, "w")) != ERR_OK)
        return rc;

    for (size_t i = 0; i < count; i++)
    {
        student_save(file, students[i]);
    }

    fclose(file);
    return rc;
}

/**
 * @brief Функция вывода таблицы студентов на экран
 */
void database_all_print(students_t *array_students, size_t count)
{
    printf("|———|————————————————————————|————————————————————|——————————|—|————————————|————————————————|—————————————————————————————————\n");
    printf("| № |        Фамилия         |        Имя         |  Группа  |G|Средний балл|Год поступления | Вариантная часть                \n");
    printf("|———|————————————————————————|————————————————————|——————————|—|————————————|————————————————|—————————————————————————————————\n");
    for (size_t i = 0; i < count; i++)
    {
        int padding = (3 - 1) / 2;
        if (i < 10 || i >= 100)
        {
            printf("|%*s%zu%*s|", padding, "", i, 3 - padding - 1, "");
            student_print(array_students[i]);
        }
        else
        {
            printf("| %zu|", i);
            student_print(array_students[i]);
        }
    }
    printf("|___|________________________|____________________|__________|_|____________|________________|\n");
}

/**
 * @brief Функция добавляет запись о студенте в таблицу
 */
int database_append(students_t *array_students, size_t *count)
{
    double score;
    short buffer_short;
    int cost, year;
    char buffer[MAX_STRING_LEN];
    int rc = ERR_OK;
    printf(">>Введите фамилию: ");
    if ((rc = input_string(buffer, MAX_SURNAME_LEN)) != ERR_OK)
        return rc;
    strncpy(array_students[*count].surname, buffer, strlen(buffer));

    printf(">>Введите имя: ");
    if ((rc = input_string(buffer, MAX_NAME_LEN)) != ERR_OK)
        return rc;
    strncpy(array_students[*count].name, buffer, strlen(buffer));

    printf(">>Введите учебную группу: ");
    if ((rc = input_string(buffer, MAX_GROUP_NAME)) != ERR_OK)
        return rc;
    strncpy(array_students[*count].group, buffer, strlen(buffer));

    printf(">>Введите пол M - мужской, F - Женский: ");
    if ((rc = input_string(buffer, 3)) != ERR_OK)
        return rc;
    array_students[*count].gender = buffer[0];

    printf(">>Введите средний балл: ");
    if (scanf("%lf", &score) != 1)
        return ERR_ADD_ORDER_INPUT;
    array_students[*count].average_score = score;
    fgetc(stdin);

    printf(">>Введите год поступления: ");
    if (scanf("%d", &year) != 1)
        return ERR_ADD_ORDER_INPUT;
    array_students[*count].admission_year = year;
    fgetc(stdin);

    printf(">>Введите тип жилья F - Квартира, H - общежитие, R - арендное: ");
    if ((rc = input_string(buffer, 3)) != ERR_OK)
        return rc;
    if (buffer[0] == 'F')
    {
        array_students[*count].type = buffer[0];

        printf(">>Введите улицу: ");
        if ((rc = input_string(buffer, MAX_STREET_LEN)) != ERR_OK)
            return rc;
        strncpy(array_students[*count].aparts.flat.street, buffer, strlen(buffer));

        printf(">>Введите номер дома: ");
        if (scanf("%hd", &buffer_short) != 1)
            return ERR_ADD_ORDER_INPUT;
        array_students[*count].aparts.flat.house_number = buffer_short;
        fgetc(stdin);

        printf(">>Введите номер квартиры: ");
        if (scanf("%hd", &buffer_short) != 1)
            return ERR_ADD_ORDER_INPUT;
        array_students[*count].aparts.flat.flat_number = buffer_short;
        fgetc(stdin);
    }
    else if (buffer[0] == 'H')
    {
        array_students[*count].type = buffer[0];

        printf(">>Введите номер общежития: ");
        if (scanf("%hd", &buffer_short) != 1)
            return ERR_ADD_ORDER_INPUT;
        array_students[*count].aparts.hostel.hostel_number = buffer_short;
        fgetc(stdin);

        printf(">>Введите номер комнаты: ");
        if (scanf("%hd", &buffer_short) != 1)
            return ERR_ADD_ORDER_INPUT;
        array_students[*count].aparts.hostel.hostel_flat = buffer_short;
        fgetc(stdin);
    }
    else if (buffer[0] == 'R')
    {
        array_students[*count].type = buffer[0];

        printf(">>Введите улицу: ");
        if ((rc = input_string(buffer, MAX_STREET_LEN)) != ERR_OK)
            return rc;
        strncpy(array_students[*count].aparts.rental.street, buffer, strlen(buffer));

        printf(">>Введите номер дома: ");
        if (scanf("%hd", &buffer_short) != 1)
            return ERR_ADD_ORDER_INPUT;
        array_students[*count].aparts.rental.house_number = buffer_short;
        fgetc(stdin);

        printf(">>Введите номер квартиры: ");
        if (scanf("%hd", &buffer_short) != 1)
            return ERR_ADD_ORDER_INPUT;
        array_students[*count].aparts.rental.flat_number = buffer_short;
        fgetc(stdin);

        printf(">>Введите стоимость аренды: ");
        if (scanf("%d", &cost) != 1)
            return ERR_ADD_ORDER_INPUT;
        array_students[*count].aparts.rental.cost = cost;
        fgetc(stdin);
    }
    else
        return ERR_ADD_ORDER_INPUT;

    (*count)++;
    return rc;
}

/**
 * @brief Функция удаляет запись о студентах, чьи имена и фамилии равны запросу
 */
int database_delete_student(students_t *array_students, size_t *count)
{
    printf(">>Функция удаляет записи студентов по имени и фамилии\n");
    char surname[MAX_SURNAME_LEN], name[MAX_NAME_LEN];
    int rc = ERR_OK;
    size_t delete_count = 0;
    printf(">>Введите фамилию: ");
    if ((rc = input_string(surname, MAX_SURNAME_LEN - 1)) != ERR_OK)
        return rc;

    printf(">>Введите имя: ");
    if ((rc = input_string(name, MAX_NAME_LEN - 1)) != ERR_OK)
        return rc;

    for (size_t i = 0; i < *count; i++)
    {
        if (strcmp(array_students[i].surname, surname) == 0 && strcmp(array_students[i].name, name) == 0)
        {
            delete_from_array(array_students, i, count);
            i--;
            delete_count++;
        }
    }

    if (delete_count == 0)
        printf(">>Нет записей, удовлетворяющих поиску\n");
    else
        printf(">>Успешно удалено %zu записей\n", delete_count);
    
    if (*count == 0)
        return ERR_EMPTY_OUTPUT;
    return ERR_OK;
}

/**
 * @brief Функция поиска по таблице.
 * Вывести список студентов указанного года поступления, живущих
 * в cъемном жилье, стоимостью меньше указанного
 */
int database_search(students_t *array_students, size_t count)
{
    size_t search_count = 0;
    printf(">>Поиск студетов по параметрам\n");
    printf("Введите год поступления: ");
    int admission_year, price;
    if (scanf("%d", &admission_year) != 1)
        return ERR_INPUT;
    fgetc(stdin);

    printf("Введите стоимость жилья: ");
    if (scanf("%d", &price) != 1)
        return ERR_INPUT;

    for (size_t i = 0; i < count; i++)
    {
        if (array_students[i].type == 'R' && array_students[i].admission_year == admission_year && array_students[i].aparts.rental.cost < price)
        {
            search_count++;
            student_print(array_students[i]);
        }
    }
    printf(">>Было найдено %zu записей\n", search_count);
    return ERR_OK;
}
