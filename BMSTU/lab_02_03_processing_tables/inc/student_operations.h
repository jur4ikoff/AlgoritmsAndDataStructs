#ifndef STUDENT_OPERATIONS
#define STUDENT_OPERATIONS

#include <stdio.h>
#include "constants.h"


typedef struct
{
    char surname[MAX_NAME_LEN];
    char name[MAX_NAME_LEN];
    char group[MAX_GROUP_NAME];
    char gender; // M - Male, F - Female
    double average_score;
    char type; // F - flat, H - hostel, R - rental
    union apartaments_type
    {
        struct flat_t
        {
            char street[MAX_STREET_LEN];
            short house_number;
            short flat_number;
        } flat;
        struct hostel_t
        {
            short hostel_number;
            short hostel_flat;
        } hostel;
        struct rental_t
        {
            char street[MAX_STREET_LEN];
            short house_number;
            short flat_number;
            int cost;
        } rental;
    } aparts;
} students_t;

int input_student(FILE *file, students_t *students, size_t count);

#endif
