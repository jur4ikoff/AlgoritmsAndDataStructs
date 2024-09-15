#include "input_number.h"

int find_exp(number_t *number, char *string)
{
    size_t len = strlen(string);
    for (size_t i = 0; i < len; i++)
    {
        if (isalpha(string[i]) != 0)
        {
            if (string[i] == 'e' || string[i] == 'E')
            {
                for (size_t j = i; j < len; j++)
                {
                    ;
                }
            }
            else
                return ERR_INPUT_CHAR;
        }
        else
            continue;
    }
    (void)*number;

    return ERR_OK;
}
