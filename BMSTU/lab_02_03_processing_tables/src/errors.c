#include "errors.h"
#include "stdio.h"

void print_error_message(short int arg)
{
    switch (arg)
    {
    case ERR_INPUT:
        printf("Error in input table\n");
        break;
    case ERR_FILENAME:
        printf("Error in filename\n");
        break;
    case ERR_UNKNOWN:
        printf("Unknown error, while runtume\n");
        break;
    }
}
