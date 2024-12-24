#ifndef HASH_H__
#define HASH_H__

#include "constants.h"
#include <stdio.h>


unsigned long long hash_char_first(char c);
unsigned long long hash_char_second(char c, unsigned long long position);
#endif
