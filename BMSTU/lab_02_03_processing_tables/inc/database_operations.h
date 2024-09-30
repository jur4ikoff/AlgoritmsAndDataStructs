#ifndef DB_OPER_H
#define DB_OPER_H

#include <stdio.h>

int database_open(FILE **file, char *filename, char *mode);
int database_choose_name(char *string);
int database_import_students(FILE *file, students_t *students, size_t *count);
#endif
