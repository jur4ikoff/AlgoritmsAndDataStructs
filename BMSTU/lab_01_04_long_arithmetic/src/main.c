// Вариант 4
#include "const.h"
#include "long_types.h"
#include "input.h"
#include "utils.h"

int main(void)
{
    long_number first_number = {0}, second_number = {0}, answer = {0};
    int rc = ERR_OK;

    if ((rc = input_int_number(&first_number)) != ERR_OK)
    {
        print_error(rc);
        return rc;
    }

    if ((rc = input_real_number(&second_number)) != ERR_OK)
    {
        print_error(rc);
        return rc;
    }

    if (second_number.mantise[0] == 0)
    {
        print_error(ERR_DIVISION_ON_ZERO);
        return ERR_DIVISION_ON_ZERO;
    }
    
    if ((rc = long_div(first_number, second_number, &answer)) != ERR_OK)
    {
        print_error(rc);
        return rc;
    }

    printf("\nResult: ");
    // print_number(answer);
    // printf("\n");
    return rc;
}
