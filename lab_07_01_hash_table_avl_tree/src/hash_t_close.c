#include "hash_t_close.h"
#include "constants.h"
#include <stdio.h>

typedef enum
{
    STATE_EMPTY,
    STATE_REMOVED,
    STAY_BUSY
} state_t;

struct __closed_hash_table_item
{
    state_t state;
    data_t data;
};

struct _closed_hash_table_type
{
    struct __closed_hash_table_item *table;
    size_t size;
};

