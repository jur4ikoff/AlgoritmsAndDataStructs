#ifndef ERRORS_H__
#define ERRORS_H__

#define ERR_OK 0
#define ERR_INPUT_OPERATION 1
#define ERR_RANGE_OPERATION 2
#define ERR_INPUT_STRING 3
#define ERR_STRING_OVERFLOW 4
#define ERR_EMPTY_STRING 5
#define ERR_FILENAME 6
#define ERR_FILE_INPUT 7
#define ERR_RANGE_MATRIX_SIZE 8

void print_error_message(short int arg);
#endif