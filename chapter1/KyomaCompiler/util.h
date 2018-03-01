// We will include this file in each file.
// Created by kyoma on 2018/2/28.
//

#ifndef KYOMACOMPILER_UTIL_H
#define KYOMACOMPILER_UTIL_H

#include "stdlib.h"
#include "assert.h"
#include "string.h"

typedef char* string;
string String(char *);

//C’s malloc function returns NULL if there is no memory left. The Tiger compiler will not have sophisticated memory management to deal with this problem. Instead, it will never call malloc directly, but call only our own function, checked_malloc, which guarantees never to return NULL
void *checked_malloc(int);


#endif //KYOMACOMPILER_UTIL_H

