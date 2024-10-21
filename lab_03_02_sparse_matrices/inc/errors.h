#ifndef ERRORS_H__
#define ERRORS_H__

#define ERR_OK 0
#define ERR_FILE_INPUT 1
#define ERR_RANGE_OPERATION 2
#define ERR_INPUT_STRING 3
#define ERR_STRING_OVERFLOW 4
#define ERR_EMPTY_STRING 5
#define ERR_FILENAME 6
#define ERR_RANGE_MATRIX_SIZE 7
#define ERR_INPUT_INTEGER_NUMBER 8
#define ERR_INPUT_INTEGER_NUMBER_RANGE 9
#define ERR_MATRIX_SIZE_NOT_EQ 10
#define ERR_MEMORY_ALLOCATION 11
void print_error_message(short int arg);
#endif