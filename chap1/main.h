//
//  main.h
//  kyomaVer
//
//  Created by kyoma on 2020/2/26.
//  Copyright © 2020 Kyoma. All rights reserved.
//

#ifndef main_h
#define main_h

typedef struct table *Table_;
typedef struct IntAndTable *IntAndTable_;

struct table{
    string id;
    int value;
    Table_ tail;
};
struct IntAndTable{
    int i;
    Table_ t;
};


struct IntAndTable interpExp(A_exp exp, Table_ t);

Table_ Table(string id, int value, struct table *tail);

Table_ interpStm(A_stm stm, Table_ tab);



#endif /* main_h */
