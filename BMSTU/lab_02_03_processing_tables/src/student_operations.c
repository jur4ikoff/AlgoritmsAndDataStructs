#include "student_operations.h"
#include "errors.h"

// Запись информации об одном студенте в файл
int input_student(FILE *file, students_t *students)
{
    char buffer[MAX_STUDENT_ORDER];
    fgets(buffer, MAX_STUDENT_ORDER, file);
    return ERR_OK;

}