// Вариант 4
#include "const.h"
#include "division.h"
#include "input_int_number.h"
#include "input_real_number.h"

int main(void)
{
    long_number first_number = {0}; // second_number = {0}, answer = {0}; // second_number;
    int rc = ERR_OK;

    printf(">> Введите первое число\n");
    if ((rc = input_int_number(&first_number)) != ERR_OK)
    {
        print_error(rc);
        return rc;
    }

    print_number(first_number);
    
    return 0;
    /*
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

    //long_number first = {.mantise = {2, 2}, .order = 2, .sign = 1, .mantise_size = 2};
    //long_number second = {.mantise = {2, 2}, .order = 1, .sign = 1, .mantise_size = 2};

    //print_number(first);
    //printf("2  ");
    //print_number(second);
    if ((rc = long_div(first_number, second_number, &answer)) != ERR_OK)
    {
        print_error(rc);
        return rc;
    }
    return rc;
    */
}
