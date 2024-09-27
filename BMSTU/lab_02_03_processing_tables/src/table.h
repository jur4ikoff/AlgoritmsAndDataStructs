#ifndef TABLE_H
#define TABLE_H
#include "constants.h"

typedef struct
{
    char surname[MAX_NAME_LEN];
    char name[MAX_NAME_LEN];
    char group[MAX_GROUP_NAME];
    int gender;
    double average_score;
    union apartaments_type
    {
        struct house
        {
            char street[MAX_STREET_LEN];
            short house_number;
            short flar_number;
        };
        struct hostel
        {
            short hostel_number;
            short hostel_flat;
        };
        struct rental
        {
            char street[MAX_STREET_LEN];
            short house_number;
            short flar_number;
            short cost;
        };
    };
} students_t;

#endif
