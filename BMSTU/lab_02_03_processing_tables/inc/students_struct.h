#ifndef TABLE_H
#define TABLE_H
#include "constants.h"

typedef enum
{
    F,
    H,
    R
} appartaments_t;

typedef struct
{
    char surname[MAX_NAME_LEN];
    char name[MAX_NAME_LEN];
    char group[MAX_GROUP_NAME];
    char gender; // M - Male, F - Female
    double average_score;
    appartaments_t type;

    union apartaments_type
    {
        struct flat_t
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
    } apart_t;
} students_t;

#endif
