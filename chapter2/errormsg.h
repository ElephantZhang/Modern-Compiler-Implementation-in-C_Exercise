//
// Created by kyoma on 2018/3/3.
//

#ifndef CHAPTER2_ERROEMSG_H
#define CHAPTER2_ERROEMSG_H

#include "util.h"
extern bool EM_anyErrors;

void EM_newline(void);

extern int EM_tokPos;

void EM_error(int, string,...);
void EM_impossible(string,...);
void EM_reset(string filename);

#endif //CHAPTER2_ERROEMSG_H
