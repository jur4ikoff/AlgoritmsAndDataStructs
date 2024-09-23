#include "const.h"
#include "long_types.h"

void copy_to_part_divisible(long_number stream, mantise_t *destination, int start, int end)
{
    destination->mantise_size = 0;
    for (int i = start; i < end; i++)
    {
        if (i < stream.mantise_size)
        {
            destination->mantise[i] = stream.mantise[i];
            destination->mantise_size++;
        }
        else
        {
            destination->mantise[i] = 0;
            destination->mantise_size++;
        }
    }
}