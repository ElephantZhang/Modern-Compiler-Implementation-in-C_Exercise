#include "stdio.h"
#include "string.h"
#include "slp.h"
#include "util.h"
#include "prog1.h"
#include "main.h"


int lookup(Table_ t, string key){
    if(t == NULL){
        printf("lookup invalid. empty link list\n");
        return -1;
    }
    if(strcmp(key, t->id)==0) return t->value;
    else return lookup(t->tail, key);
}

Table_ update(Table_ t, string key, int value){
    return Table(key, value, t);
    //just insert to the head...
}

Table_ Table(string id, int value, struct table *tail){
    Table_ t = malloc(sizeof(*t));
    t->id = id;
    t->value = value;
    t->tail = tail;
    return t;
}

IntAndTable_ intAndTable(int val, Table_ t){
    IntAndTable_ iat = malloc(sizeof(*iat));
    iat->i = val;
    iat->t = t;
    return iat;
}



int maxargs(A_stm stm){
    int sum = 0;
    if(stm->kind == A_compoundStm){
        return maxargs(stm->u.compound.stm1) + maxargs(stm->u.compound.stm2);
    }else if(stm->kind == A_assignStm){
        if(stm->u.assign.exp->kind == A_eseqExp){
            return maxargs(stm->u.assign.exp->u.eseq.stm);
        }
    }else{// kind is A_printStm
        A_expList expList = stm->u.print.exps;
        ++sum;
        while(expList->kind == A_pairExpList){
            A_exp exp = expList->u.pair.head;
            if(exp->kind == A_eseqExp){
                sum += maxargs(exp->u.eseq.stm);
            }
            expList = expList->u.pair.tail;
        }
    }
    return sum;
}
void interp(A_stm stm){
    Table_ tab = NULL;
    if(stm->kind==A_compoundStm){
        interp(stm->u.compound.stm1);
        interp(stm->u.compound.stm2);
    }else{// kind is assignStm or printStm
        tab = interpStm(stm, tab);
    }
}

Table_ interpStm(A_stm stm, Table_ tab){
    if(stm->kind==A_compoundStm){
        tab = interpStm(stm->u.compound.stm1, tab);
        tab = interpStm(stm->u.compound.stm2, tab);
    }else if(stm->kind==A_assignStm){
        tab = update(tab, stm->u.assign.id, interpExp(stm->u.assign.exp, tab).i );
    }else{//kind is print stm
        if(stm->u.print.exps->kind==A_pairExpList){
            A_expList expList = stm->u.print.exps;
            while(expList->kind == A_pairExpList){
                A_exp exp = expList->u.pair.head;
                printf("%d ", interpExp(exp, tab).i);
                expList = expList->u.pair.tail;
            }
            printf("%d", interpExp(expList->u.last, tab).i);
        }else{//kind of expList is LastExpList
            printf("%d", interpExp(stm->u.print.exps->u.last, tab).i);
        }
        printf("\n");
    }
    return tab;
}

struct IntAndTable interpExp(A_exp exp, Table_ t){
    if(exp->kind==A_idExp){
        return *intAndTable(lookup(t, exp->u.id), t);
    }else if(exp->kind==A_numExp){
        return *intAndTable(exp->u.num, t);
    }else if(exp->kind==A_opExp){
        int a = interpExp(exp->u.op.left, t).i, b = interpExp(exp->u.op.right, t).i, ans;
        if(exp->u.op.oper == A_plus){
            ans = a+b;
        }else if(exp->u.op.oper==A_minus){
            ans = a-b;
        }else if(exp->u.op.oper==A_times){
            ans = a*b;
        }else{//operator is divide
            ans = a/b;
        }
        return *intAndTable(ans, t);
    }else{//kind is EseqExp
        interpStm(exp->u.eseq.stm, t);
        return interpExp(exp->u.eseq.exp, t);
    }
}

int main(){
    A_stm stm = prog();
    printf("maxargs: %d\n", maxargs(stm) );
    Table_ tab = NULL;
    interpStm(stm, tab);
    return 0;
}
