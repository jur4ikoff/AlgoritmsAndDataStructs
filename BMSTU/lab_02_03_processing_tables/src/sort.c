#include "sort.h"
#include "table.h"
#include <string.h>

int compare_surnames(const void *a, const void *b)
{
    students_t *students_a = (students_t *)a;
    students_t *students_b = (students_t *)b;
    // Сравнение по полю surname
    return strcmp(students_a->surname, students_b->surname);
}

/*void mysort(void *base, size_t number, size_t width, int (*compare)(const void *, const void *))
{
    
}*/