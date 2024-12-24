#include "hash.h"
#include <stdio.h>

// Функция для хэширования одного символа
unsigned long long hash_char_first(char c)
{
    return (unsigned long long)c;
}

// Функция для хэширования одного символа
unsigned long long hash_char_second(char c, unsigned long long position)
{
    int prime1 = 31;
    int prime2 = 53;
    int shift = 16;

    unsigned long long hash = (unsigned long long)c * prime1 + position * prime2;
    hash = (hash ^ (hash >> shift)); // XOR с правым сдвигом для улучшения распределения
    return hash;   // Возвращаем остаток от деления на размер таблицы
}
