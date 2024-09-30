#ifndef DB_OPER_H
#define DB_OPER_H

#include <stdio.h>

int database_open(FILE **file, char *filename, char *mode);
int database_choose_name(char *string);

#endif
