#include "errors.h"

void print_error(int arg)
{
    switch (arg)
    {
    case ERR_INPUT_CHAR:
        printf("Error, number must not contain any characters\n");
        break;
    case ERR_MANTISE_SIZE:
        printf("Error in mantise size. It's must be short then 40 digits\n");
        break;
    case ERR_ORDER_SIZE:
        printf("Error in order size. It's must be short then 5 digits\n");
        break;
    case ERR_OVERFLOW:
        printf("Error, overflow\n");
        break;
    case ERR_INPUT:
        printf("Error while input\n");
        break;
    case ERR_NOT_FLOAT:
        printf("Error, input number not a real number\n");
        break;
    case ERR_ORDER_CHAR:
        printf("Error, order contain char\n");
        break;
    case ERR_POINTS_COUNT:
        printf("Error, point must be only one\n");
        break;
    case ERR_EMPTY_INPUT:
        printf("Error, input is empty");
        break;
    case ERR_DIVISION_ON_ZERO:
        printf("Erorr, division on zero\n");
        break;
    }
}
