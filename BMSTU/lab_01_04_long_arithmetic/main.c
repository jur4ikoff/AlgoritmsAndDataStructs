// Вариант 4

#include "const.h"
#include "io.h"
#include "division.h"

int main(void)
{
    number_t first_number = {0}, second_number = {0}, answer = {0}; // second_number;
    int rc = ERR_OK;

    char line[] = {">>---------1---------2---------3---------4"}; // без \n

    printf(">> Введите первое число\n");
    if ((rc = input_number(&first_number, line)) != ERR_OK)
    {
        print_error(rc);
        return rc;
    }

    printf("\n");
    //print_number(first_number);

    printf(">> Введите второе число\n");
    if ((rc = input_number(&second_number, line)) != ERR_OK)
    {
        print_error(rc);
        return rc;
    }

    //print_number(second_number);

    if (second_number.mantise[0] == 0)
    {
        print_error(ERR_DIVISION_ON_ZERO);
        return ERR_DIVISION_ON_ZERO;
    }

    if ((rc =  long_div(first_number, second_number, &answer)) != ERR_OK)
    {
        print_error(rc);
        return rc;
    }
    return rc;
}
