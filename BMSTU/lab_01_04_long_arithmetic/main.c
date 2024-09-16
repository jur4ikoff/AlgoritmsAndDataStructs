// Вариант 4

#include "const.h"
#include "io.h"

int main(void)
{
    number_t first_number = {0}; // second_number;
    int rc = ERR_OK;
    printf("%hd %hd %hd\n", first_number.sign, first_number.mantise_size, first_number.order);

    if ((rc = input_number(&first_number)) != ERR_OK)
    {
        print_error(rc);
        return rc;
    }
    
    return rc;
}
