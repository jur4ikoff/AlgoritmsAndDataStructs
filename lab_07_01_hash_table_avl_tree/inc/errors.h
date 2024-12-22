#ifndef ERRORS_H__
#define ERRORS_H__

#define ERR_OK 0
#define ERR_STRING 1
#define ERR_OPERATION 2
#define ERR_MEMORY_ALLOCATION 3
#define ERR_DATA_INPUT 4
#define ERR_FILE 5
#define ERR_FORK 6
#define ERR_HEAD 7


#define WARNING_REPEAT -1
#define WARNING_TREE -2
#define WARNING_ELEMENT_NOT_FOUND -3
#define WARNING_OPERATION -4

typedef short error_t;
#endif
