#ifndef DB_OPER_H
#define DB_OPER_H

#include <stdio.h>
#include "student_operations.h"

int database_open(FILE **file, char *filename, char *mode);
int database_choose_name(char *string);
int database_import_students(FILE *file, students_t *students, size_t *count);
int database_save(char *filename, students_t *students, size_t count);
void database_print(students_t *array_students, size_t count);
int database_append(students_t *array_students, size_t *count);
int database_delete_student(students_t *students, size_t *count);
int database_search(students_t *array_students, size_t count);

#endif
