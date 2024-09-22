// Вариант 4
#include "const.h"
#include "division.h"
#include "input_int_number.h"
#include "input_real_number.h"

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
    // print_number(first_number);

    printf(">> Введите второе число\n");
    if ((rc = input_number(&second_number, line)) != ERR_OK)
    {
        print_error(rc);
        return rc;
    }

    // print_number(second_number);

    if (second_number.mantise[0] == 0)
    {
        print_error(ERR_DIVISION_ON_ZERO);
        return ERR_DIVISION_ON_ZERO;
    }

    //number_t first = {.mantise = {2, 2}, .order = 2, .sign = 1, .mantise_size = 2};
    //number_t second = {.mantise = {2, 2}, .order = 1, .sign = 1, .mantise_size = 2};

    /*print_number(first_number);
    printf("2  ");
    print_number(second_number);*/

    //print_number(first);
    //printf("2  ");
    //print_number(second);
    if ((rc = long_div(first_number, second_number, &answer)) != ERR_OK)
    {
        print_error(rc);
        return rc;
    }
    return rc;
}
