// This header file's unique prefix is 'A'
// Created by kyoma on 2018/2/28.
//

#ifndef KYOMACOMPILER_LANGUAGETREE_H
#define KYOMACOMPILER_LANGUAGETREE_H

/*
 * stm == statement
 * exp == expression
 * binop == binary operator
 * eseq == expression sequence
 *
 * Programming style:
    1. Trees are described by a grammar.
    2. A tree is described by one or more typedefs, corresponding to a symbol in the grammar.
    3. Each typedef defines a pointer to a corresponding struct. The struct name, which ends in an underscore, is never used anywhere except in the declaration of the typedef and the definition of the struct itself.
    4. Each struct contains a kind field, which is an enum showing different variants, one for each grammar rule; and a u field, which is a union.
    5. If there is more than one nontrivial (value-carrying) symbol in the right-hand side of a rule (example: the rule CompoundStm), the union will have a component that is itself a struct comprising these values (example: the compound element of the A_stm_ union)
    6. If there is only one nontrivial symbol in the right-hand side of a rule, the union will have a component that is the value (example: the num field of the A_exp union).
    7. Every class will have a constructor function that initializes all the fields. The malloc function shall never be called directly, except in these constructor functions
    8. Each module (header file) shall have a prefix unique to that module
    9. Typedef names (after the prefix) shall start with lowercase letters; constructor functions (after the prefix) with uppercase; enumeration atoms (after the prefix) with lowercase; and union variants (which have no prefix) with lowercase.
 */
#include "util.h"

typedef char* string;

typedef struct A_stm_* A_stm;
typedef struct A_exp_* A_exp;
typedef struct A_expList_ *A_expList;
typedef struct table* Table_;
typedef enum {
    A_plus, A_minus, A_times, A_div
} A_binop;

struct A_stm_{
    enum {
        A_compoundStm,
        A_assignStm,
        A_printStm
    }kind;
    union{
        struct {
            A_stm stm1, stm2;
        } compound;
        struct {
            string id;
            A_exp exp;
        } assign;
        struct {
            A_expList exps;
        }print;
    }u;
};

struct A_exp_{
    enum {
        A_idExp,
        A_numExp,
        A_opExp,
        A_eseqExp
    } kind;
    union {
        string id;
        int num;
        struct{
            A_exp left;
            A_binop oper;
            A_exp right;
        } op;
        struct {
            A_stm stm;
            A_exp exp;
        } eseq;
    } u;
};


struct A_expList_{
    enum {
        A_pairExpList,
        A_lastExpList
    } kind;
    union {
        struct {
            A_exp head;
            A_expList tail;
        } pair;
        A_exp last;
    }u;
};

struct table{
    string id;
    int value;
    Table_ tail;
};

struct IntAndTable {
    int i;
    Table_ t;
};

Table_ Table(string, int, struct table*);

// interp == interpret
Table_ interpStm(A_stm, Table_);

A_stm A_CompoundStm(A_stm stm1, A_stm stm2);
A_stm A_AssignStm(string id, A_exp exp);
A_stm A_PrintStm(A_expList exps);
A_exp A_IdExp(string id);
A_exp A_NumExp(int num);
A_exp A_OpExp(A_exp left, A_binop oper, A_exp right);
A_exp A_EseqExp(A_stm stm, A_exp exp);
A_expList A_PairExpList(A_exp, A_expList);
A_expList A_LastExpList(A_exp);


// Chapter One's Programming Exercise
int maxargs(A_stm);
int expListNumberCount(A_expList, int*);
int max(int, int);
struct IntAndTable interpExp(A_exp, Table_);
Table_ update(Table_, string, int);
int lookup(Table_, string);
void interpExpList(A_expList, Table_);

#endif //KYOMACOMPILER_LANGUAGETREE_H
