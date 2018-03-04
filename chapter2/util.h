//
// Created by kyoma on 2018/3/3.
//

#ifndef CHAPTER2_UTIL_H
#define CHAPTER2_UTIL_H
#include <assert.h>
#include "stdlib.h"

typedef char *string;
typedef char bool;

#define TRUE 1
#define FALSE 0

void *checked_malloc(int);
string String(char *);

typedef struct U_boolList_ *U_boolList;
struct U_boolList_ {bool head; U_boolList tail;};
U_boolList U_BoolList(bool head, U_boolList tail);


#endif //CHAPTER2_UTIL_H
