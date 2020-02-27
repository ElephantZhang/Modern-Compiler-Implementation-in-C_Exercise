//
//  bst.c
//  k_chap1
//
//  Created by kyoma on 2020/2/27.
//  Copyright © 2020 Kyoma. All rights reserved.
//

//Exercises 1.1 persistent funcional binary search tree
#include "bst.h"

T_tree Tree(T_tree l, T_binding bd, T_tree r){
    T_tree t = checked_malloc(sizeof(*t));
    t->left = l;
    t->binding = bd;
    t->right = r;
    return t;
}
T_tree insert(string key, void *binding, T_tree t){
    if(t==NULL) return Tree(NULL, binding, NULL);
    
    else if(strcmp(key, t->binding->key)<0){
        return Tree(insert(key, binding, t->left), t->binding, t->right);
    }else if(strcmp(key, t->binding->key)>0){
        return Tree(t->left, t->binding, insert(key, binding, t->right));
    }else return Tree(t->left, t->binding, t->right);
}

void *T_lookup(string key, T_tree t){
    if(t==NULL) return FALSE;
    if(strcmp(key, t->binding->key)<0){
        return T_lookup(t->binding->key, t->left);
    }else if(strcmp(key, t->binding->key)>0){
        return T_lookup(t->binding->key, t->right);
    }else return t->binding;

}

bool member(T_tree t, string key){
    if(t==NULL) return FALSE;
    
    if(strcmp(key, t->binding->key)<0){
        return member(t->left, key);
    }else if(strcmp(key, t->binding->key)>0){
        return member(t->right, key);
    }else return TRUE;
}


/*
 TODO:(may never do)
 Balanced search trees, rebalance on insertion.
 */
