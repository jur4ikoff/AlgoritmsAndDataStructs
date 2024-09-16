// Вариант 4

#include "const.h"
#include "io.h"

int main(void)
{
    number_t first_number = {0}; // second_number;
    int rc = ERR_OK;

    char line[] = {">>----------1----------2----------3----------4"}; // без \n
    if ((rc = input_number(&first_number, line)) != ERR_OK)
    {
        print_error(rc);
        return rc;
    }
    print_number(first_number);
    return rc;
}
