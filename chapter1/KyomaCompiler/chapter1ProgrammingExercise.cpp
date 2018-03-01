//
// Created by kyoma on 2018/3/1.
//
#include "stdio.h"
#include "languageTree.h"

int max(int a, int b){
    if(a>b) return a;
    else return b;
}


int expListNumberCount(A_expList expL, int &maximum){
    int sum = 0;
    if(expL->kind == expL->A_pairExpList){
        sum = expListNumberCount(expL->u.pair.tail, maximum) + 1;
        A_exp exp = expL->u.last;
        if(exp->kind == exp->A_eseqExp){
            maximum = max(maximum, maxargs(exp->u.eseq.stm));
        }
    }else{
        sum = 1;
    }
    return sum;
}

int maxargs(A_stm st){
    int ans = 0;
    if(st->kind == st->A_compoundStm){
        int now = max(maxargs(st->u.compound.stm1), maxargs(st->u.compound.stm2));
        ans = max(now, ans);
    }else if(st->kind == st->A_assignStm){
        A_exp p = st->u.assign.exp;
        if(p->kind == p->A_eseqExp){
            ans = max(ans, maxargs(p->u.eseq.stm));
        }
    }else{ // the statement is a print statement
        ans = max(ans, expListNumberCount(st->u.print.exps, ans));
    }
    return ans;
}//tell the maximum number of arguments of any print statement

// interp == interpret
Table_ interpStm(A_stm s, Table_ t){
    if(s->kind == s->A_assignStm){
        struct IntAndTable val = interpExp(s->u.assign.exp, t);
        t = update(t, s->u.assign.id, val.i);
    }else if(s->kind == s->A_printStm){
        interpExpList(s->u.print.exps, t);
    }else{
        t = interpStm(s->u.compound.stm1, t);
        t = interpStm(s->u.compound.stm2, t);
    }
    return t;
};

void interpExpList(A_expList expL, Table_ t){
    if(expL->kind == expL->A_lastExpList){
        interpExp(expL->u.last, t);
    }else{
        interpExp(expL->u.pair.head, t);
        interpExpList(expL->u.pair.tail ,t);
    }
}


Table_ update(Table_ t, string key, int val){
    Table_ now = Table(key, val, t);
    return now;
}

int lookup(Table_ t, string key){
    Table_ p = t;
    while(p != NULL){
        if(strcmp(key, p->id) == 0){
            return p->value;
        }else{
            ++p;
        }
    }
    return 0;
}

struct IntAndTable interpExp(A_exp exp, Table_ t){
    struct IntAndTable now;
    now.t = t;
    if(exp->kind == exp->A_idExp){
        now.i = lookup(t, exp->u.id);
    }else if(exp->kind == exp->A_numExp){
        now.i = exp->u.num;
    }else if(exp->kind == exp->A_opExp){
        int a, b;
        a = interpExp(exp->u.op.left, t).i;
        b = interpExp(exp->u.op.right, t).i;
        if(exp->u.op.oper == A_plus){
            now.i = a + b;
        }else if(exp->u.op.oper == A_minus){
            now.i = a - b;
        }else if(exp->u.op.oper == A_times){
            now.i = a * b;
        }else{
            now.i = a / b;
        }
    }else{
        now.i = interpExp(exp->u.eseq.exp, t).i;
        now.t = interpStm(exp->u.eseq.stm, t);
    }
    return now;
}


A_stm A_CompoundStm(A_stm stm1, A_stm stm2) {
    A_stm s = (A_stm)checked_malloc(sizeof *s);
    s->kind=s->A_compoundStm; s->u.compound.stm1=stm1; s->u.compound.stm2=stm2;
    return s;
}


A_stm A_AssignStm(string id, A_exp exp) {
    A_stm s = (A_stm)checked_malloc(sizeof *s);
    s->kind=s->A_assignStm; s->u.assign.id=id; s->u.assign.exp=exp;
    return s;
}

A_stm A_PrintStm(A_expList exps) {
    A_stm s = (A_stm)checked_malloc(sizeof *s);
    s->kind=s->A_printStm; s->u.print.exps=exps;
    return s;
}

A_exp A_IdExp(string id) {
    A_exp e = (A_exp)checked_malloc(sizeof *e);
    e->kind=e->A_idExp; e->u.id=id;
    return e;
}

A_exp A_NumExp(int num) {
    A_exp e = (A_exp)checked_malloc(sizeof *e);
    e->kind=e->A_numExp; e->u.num=num;
    return e;
}

A_exp A_OpExp(A_exp left, A_binop oper, A_exp right) {
    A_exp e = (A_exp)checked_malloc(sizeof *e);
    e->kind=e->A_opExp; e->u.op.left=left; e->u.op.oper=oper; e->u.op.right=right;
    return e;
}

A_exp A_EseqExp(A_stm stm, A_exp exp) {
    A_exp e = (A_exp)checked_malloc(sizeof *e);
    e->kind=e->A_eseqExp; e->u.eseq.stm=stm; e->u.eseq.exp=exp;
    return e;
}

A_expList A_PairExpList(A_exp head, A_expList tail) {
    A_expList e = (A_expList)checked_malloc(sizeof *e);
    e->kind=e->A_pairExpList; e->u.pair.head=head; e->u.pair.tail=tail;
    return e;
}

A_expList A_LastExpList(A_exp last) {
    A_expList e = (A_expList)checked_malloc(sizeof *e);
    e->kind=e->A_lastExpList; e->u.last=last;
    return e;
}

Table_ Table(string id, int value, Table_ tail){
    Table_ t = (Table_)malloc(sizeof(*t));
    t->id = id;
    t->value = value;
    t->tail = tail;
    return t;
};


void *checked_malloc(int len){
    void *p = malloc(len);
    assert(p);
    return p;
};




