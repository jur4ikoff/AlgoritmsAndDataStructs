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
        struct house_t
        {
            char street[MAX_STREET_LEN];
            short house_number;
            short flar_number;
        } house;
        struct hostel_t
        {
            short hostel_number;
            short hostel_flat;
        } hostel;
        struct rental_t
        {
            char street[MAX_STREET_LEN];
            short house_number;
            short flar_number;
            short cost;
        } rental;
    };
} students_t;

#endif
