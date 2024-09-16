// Вариант 4

#include "const.h"
#include "io.h"


int main(void)
{
    number_t first_number = {0}; // second_number;
    // printf("%hd %s %hd\n", first_number.sign, first_number.mantise, first_number.order);
    int rc = ERR_OK;


    if ((rc = input_number(&first_number)) != ERR_OK)
    {
        print_error(rc);
        return rc;
    }

    return rc;
    
}
