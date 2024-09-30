#ifndef ERRORS_H
#define ERRORS_H

#define ERR_OK 0
#define ERR_INPUT 1
#define ERR_FILENAME 2
#define ERR_OPERATION_INPUT 3
#define ERR_OPERATION_COUNT 4
#define ERR_STRING_OVERFLOW 5
#define ERR_UNKNOWN 100

void print_error_message(short int arg);
void help(void);
#endif
