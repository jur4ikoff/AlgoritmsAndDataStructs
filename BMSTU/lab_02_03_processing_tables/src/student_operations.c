#include "student_operations.h"
#include "errors.h"
#include <string.h>
#include <stdlib.h>
#include <errno.h>

// Конвертация строки в double
int string_to_double(const char *str, double *result, size_t count)
{
    char string[MAX_MANTISE_SIZE], *endptr;
    strncpy(string, str, count);
    string[count] = 0;

    errno = 0; // Сбрасываем errno перед вызовом strtod
    *result = strtod(string, &endptr);

    // Проверяем ошибки
    if (errno == ERANGE)
    {
        printf("Ошибка: число выходит за пределы допустимого диапазона.\n");
        return ERR_CONVERTATION_DOUBLE; // Можно также выбросить ошибку или обработать иначе
    }

    // Проверяем, было ли преобразование успешным
    if (endptr == string)
    {
        printf("Ошибка: строка не содержит валидного числа.\n");
        return ERR_CONVERTATION_DOUBLE; // Или иная обработка ошибки
    }

    if (*endptr != 0)
        return ERR_CONVERTATION_DOUBLE;

    // Успешное преобразование
    return ERR_OK;
}

// Получение информации об одном студенте из файла
int student_input(FILE *file, students_t *students, size_t count)
{
    int rc, spaces, token_len;
    char buffer[MAX_STUDENT_ORDER];
    if (!fgets(buffer, MAX_STUDENT_ORDER, file))
    {
        if (feof(file))
            return END_OF_FILE;
        else
            return ERR_FILE_ORDER_INPUT;
    }
    char *newline = strchr(buffer, '\n');
    if (!newline)
        return ERR_FILE_ORDER_OVERFLOW;
    *newline = 0;

    char *ptr = buffer;
    if (*ptr == '\0')
        return ERR_FILE_ORDER_INPUT;

    spaces = strspn(ptr, SPACES);
    ptr += spaces;
    if (*ptr == '\0')
        return ERR_FILE_ORDER_INPUT;

    token_len = strcspn(ptr, DELIMETER);
    if (token_len > MAX_SURNAME_LEN)
        return ERR_TOO_LONG_FIELD;
    strncpy(students[count].surname, ptr, token_len);
    ptr += token_len + 1;
    if (*ptr == '\0')
        return ERR_FILE_ORDER_INPUT;

    token_len = strcspn(ptr, DELIMETER);
    if (token_len > MAX_NAME_LEN)
        return ERR_TOO_LONG_FIELD;
    strncpy(students[count].name, ptr, token_len);
    ptr += token_len + 1;
    if (*ptr == '\0')
        return ERR_FILE_ORDER_INPUT;

    token_len = strcspn(ptr, DELIMETER);
    if (token_len > MAX_GROUP_NAME)
        return ERR_TOO_LONG_FIELD;
    strncpy(students[count].group, ptr, token_len);
    ptr += token_len + 1;
    if (*ptr == '\0')
        return ERR_FILE_ORDER_INPUT;

    token_len = strcspn(ptr, DELIMETER);
    if (token_len > 1)
        return ERR_TOO_LONG_FIELD;

    if (*ptr == 'M' || *ptr == 'F')
        students[count].gender = *ptr;
    else
        return ERR_UNKNOWN_GENDER;
    ptr += 2;
    if (*ptr == '\0')
        return ERR_FILE_ORDER_INPUT;

    token_len = strcspn(ptr, DELIMETER);
    if (token_len > MAX_MANTISE_SIZE)
        return ERR_TOO_LONG_FIELD;
    double average_score;
    if ((rc = string_to_double(ptr, &average_score, token_len)) != ERR_OK)
        return rc;
    students[count].average_score = average_score;
    ptr += token_len + 1;
    if (*ptr == '\0')
        return ERR_FILE_ORDER_INPUT;

    double year;
    if ((rc = string_to_double(ptr, &year, token_len)) != ERR_OK)
        return rc;
    students[count].admission_year = (int)year;
    ptr += token_len + 1;
    if (*ptr == '\0')
        return ERR_FILE_ORDER_INPUT;

    token_len = strcspn(ptr, DELIMETER);
    if (token_len > 1)
        return ERR_TOO_LONG_FIELD;

    students[count].type = *ptr;
    // TO DO Оптимизация ифа
    if (*ptr == 'F')
    {
        ptr += 2;
        token_len = strcspn(ptr, DELIMETER);
        if (token_len > MAX_STREET_LEN)
            return ERR_TOO_LONG_FIELD;
        strncpy(students[count].aparts.flat.street, ptr, token_len);
        ptr += token_len + 1;
        if (*ptr == '\0')
            return ERR_FILE_ORDER_INPUT;

        token_len = strcspn(ptr, DELIMETER);
        if (token_len > MAX_SHORT_SIZE)
            return ERR_TOO_LONG_FIELD;
        double house_number;
        if ((rc = string_to_double(ptr, &house_number, token_len)) != ERR_OK)
            return rc;
        students[count].aparts.flat.house_number = (short)house_number;
        ptr += token_len + 1;
        if (*ptr == '\0')
            return ERR_FILE_ORDER_INPUT;

        token_len = strcspn(ptr, DELIMETER);
        if (token_len > MAX_SHORT_SIZE)
            return ERR_TOO_LONG_FIELD;
        double flat_number;
        if ((rc = string_to_double(ptr, &flat_number, token_len)) != ERR_OK)
            return rc;
        students[count].aparts.flat.flat_number = (short)flat_number;
        ptr += token_len;
        if (*ptr == '\0')
            return ERR_OK;
    }
    else if (*ptr == 'H')
    {
        ptr += 2;
        token_len = strcspn(ptr, DELIMETER);
        if (token_len > MAX_SHORT_SIZE)
            return ERR_TOO_LONG_FIELD;
        double hostel_number;
        if ((rc = string_to_double(ptr, &hostel_number, token_len)) != ERR_OK)
            return rc;
        students[count].aparts.hostel.hostel_number = (short)hostel_number;
        ptr += token_len + 1;
        if (*ptr == '\0')
            return ERR_FILE_ORDER_INPUT;

        token_len = strcspn(ptr, DELIMETER);
        if (token_len > MAX_SHORT_SIZE)
            return ERR_TOO_LONG_FIELD;
        double hostel_flat;
        if ((rc = string_to_double(ptr, &hostel_flat, token_len)) != ERR_OK)
            return rc;
        students[count].aparts.hostel.hostel_flat = (short)hostel_flat;
        ptr += token_len;
        if (*ptr == '\0')
            return ERR_OK;
    }
    else if (*ptr == 'R')
    {
        ptr += 2;

        token_len = strcspn(ptr, DELIMETER);
        if (token_len > MAX_STREET_LEN)
            return ERR_TOO_LONG_FIELD;
        strncpy(students[count].aparts.rental.street, ptr, token_len);
        ptr += token_len + 1;
        if (*ptr == '\0')
            return ERR_FILE_ORDER_INPUT;

        token_len = strcspn(ptr, DELIMETER);
        if (token_len > MAX_SHORT_SIZE)
            return ERR_TOO_LONG_FIELD;
        double house_number;
        if ((rc = string_to_double(ptr, &house_number, token_len)) != ERR_OK)
            return rc;
        students[count].aparts.rental.house_number = (short)house_number;
        ptr += token_len + 1;
        if (*ptr == '\0')
            return ERR_FILE_ORDER_INPUT;

        token_len = strcspn(ptr, DELIMETER);
        if (token_len > MAX_SHORT_SIZE)
            return ERR_TOO_LONG_FIELD;
        double flat_number;
        if ((rc = string_to_double(ptr, &flat_number, token_len)) != ERR_OK)
            return rc;
        students[count].aparts.rental.flat_number = (short)flat_number;
        ptr += token_len + 1;
        if (*ptr == '\0')
            return ERR_OK;

        token_len = strcspn(ptr, DELIMETER);
        if (token_len > MAX_INT_SIZE)
            return ERR_TOO_LONG_FIELD;
        double cost;
        if ((rc = string_to_double(ptr, &cost, token_len)) != ERR_OK)
            return rc;
        students[count].aparts.rental.cost = (int)cost;
        ptr += token_len;
        if (*ptr == '\0')
            return ERR_OK;
    }
    else
        return ERR_UNKNOWN_TYPE;

    return ERR_OK;
}

/**
 * @brief Сохранение структуры одного студента в файл
 * @param
 * @param
 * @return
 */
void student_save(FILE *file, students_t student)
{
    fprintf(file, "%s;%s;%s;%c;%.2f;%d;%c;", student.surname, student.name, student.group, student.gender, student.average_score, student.admission_year, student.type);
    if (student.type == 'F')
    {
        fprintf(file, "%s;%d;%d\n", student.aparts.flat.street, student.aparts.flat.house_number, student.aparts.flat.flat_number);
    }
    else if (student.type == 'H')
    {
        fprintf(file, "%d;%d\n", student.aparts.hostel.hostel_number, student.aparts.hostel.hostel_flat);
    }
    else if (student.type == 'R')
    {
        fprintf(file, "%s;%d;%d;%d\n", student.aparts.rental.street, student.aparts.rental.house_number, student.aparts.rental.flat_number, student.aparts.rental.cost);
    }
}

/**
 * @brief Вывод структуры студента на экран
 * @param
 * @param
 * @return
 */
void student_print(students_t student)
{
    int padding = (MAX_SURNAME_LEN - (int)strlen(student.surname)) / 2;
    printf("%*s%s%*s|", padding, "", student.surname, MAX_SURNAME_LEN - padding - (int)strlen(student.surname), "");

    padding = (MAX_NAME_LEN - (int)strlen(student.name)) / 2;
    printf("%*s%s%*s|", padding, "", student.name, MAX_NAME_LEN - padding - (int)strlen(student.name), "");

    padding = (MAX_GROUP_NAME - (int)strlen(student.group)) / 2;
    printf("%*s%s%*s|", padding, "", student.group, MAX_GROUP_NAME - padding - (int)strlen(student.group), "");
    printf("%c|", student.gender);

    printf("%*s%4.2f%*s|", 4, "", student.average_score, 4, "");
    printf("%*s%d%*s|", 6, "", student.admission_year, 6, "");
    if (student.type == 'F')
    {
        printf(" %*sКвартира%*s ", 1, "", 1, "");

        padding = (MAX_STREET_LEN - (int)strlen(student.aparts.flat.street)) / 2;
        printf("%*s%s%*s ", padding, "", student.aparts.flat.street, MAX_STREET_LEN - padding - (int)strlen(student.group), "");
    
        printf("%*s%d%*s ", 2, "", student.aparts.flat.house_number, 2, "");
        printf("%*s%d%*s|", 2, "", student.aparts.flat.flat_number, 2, "");
        // а %s %d %d\n", student.aparts.flat.street, student.aparts.flat.house_number, student.aparts.flat.flat_number);
    }
    else if (student.type == 'H')
    {
        printf(" %*sОбщежитие%*s ", 0, "", 1, "");

        
        //%d %d\n", student.aparts.hostel.hostel_number, student.aparts.hostel.hostel_flat);
    }
    else if (student.type == 'R')
    {
        printf(" %*sАренда%*s ", 2, "", 2, "");
        // printf(" Аренда %s %d %d %d\n", student.aparts.rental.street, student.aparts.rental.house_number, student.aparts.rental.flat_number, student.aparts.rental.cost);
    }
    printf("\n");
}
