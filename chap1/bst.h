//
//  bst.h
//  k_chap1
//
//  Created by kyoma on 2020/2/27.
//  Copyright © 2020 Kyoma. All rights reserved.
//

#ifndef bst_h
#define bst_h

#include "stdio.h"
#include "util.h"
#include "string.h"

typedef struct tree *T_tree;
typedef struct binding *T_binding;
struct tree{
    T_tree left;
    T_binding binding;
    T_tree right;
};
struct binding{
    string key;
    void *value;
};
T_binding Binding(string key, void *value){
    T_binding bd = checked_malloc(sizeof(*bd));
    bd->key = key;
    bd->value = value;
    return bd;
}
T_tree Tree(T_tree l, T_binding bd, T_tree r);
T_tree insert(string key, void *binding, T_tree t);
void *T_lookup(string key, T_tree t);//conflict with lookup in main.c
bool member(T_tree t, string key);

#endif /* bst_h */
