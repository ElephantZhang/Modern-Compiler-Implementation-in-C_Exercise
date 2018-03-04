%{
#include <string.h>
#include "util.h"
#include "tokens.h"
#include "errormsg.h"

int charPos=1;

int yywrap(void)
{
    charPos=1;
    return 1;
}


void adjust(void)
{
    EM_tokPos=charPos;
    charPos+=yyleng;
}

%}

%%
\".*?\"     {adjust(); yylval.sval=String(yytext); return STRING;}
\/\*.*?\*\/     {adjust(); EM_newline()}


" "	 {adjust(); continue;}
\n	 {adjust(); EM_newline(); continue;}
","	 {adjust(); return COMMA;}
.	 {adjust(); EM_error(EM_tokPos,"illegal token");}
":"     {adjust(); return COLON;}
";"     {adjust(); return SEMICOLON;}
"("     {adjust(); return LPAREN;}
")"     {adjust(); return RPAREN;}
"["     {adjust(); return LBRACK;}
"]"     {adjust(); return RBRACK;}
"{"     {adjust(); return LBRACE;}
"}"     {adjust(); return RBRACE;}
"."     {adjust(); return DOT;}
"+"     {adjust(); return PLUS;}
"-"     {adjust(); return MINUS;}
"*"     {adjust(); return TIMES;}
"/"     {adjust(); return DIVIDE;}
"=="     {adjust(); return EQ;}
"<>"    {adjust(); return NEQ;}
"<"     {adjust(); return LT;}
"<="    {adjust(); return LE;}
">"     {adjust(); return GT;}
">="    {adjust(); return GE;}
"&"     {adjust(); return AND;}
"|"     {adjust(); return OR;}
":="    {adjust(); return ASSIGN;}

[0-9]+	 {adjust(); yylval.ival=atoi(yytext); return INT;}

array    {adjust(); return ARRAY;}
for  	 {adjust(); return FOR;}
if       {adjust(); return IF;}
then     {adjust(); return THEN;}
else     {adjust(); return ELSE;}
while    {adjust(); return WHILE;}
to       {adjust(); return TO;}
do       {adjust(); return DO;}
let      {adjust(); return LET;}
in       {adjust(); return IN;}
end      {adjust(); return END;}
of       {adjust(); return OF;}
break    {adjust(); return BREAK;}
nil      {adjust(); return NIL;}
function {adjust(); return FUNCTION;}
var      {adjust(); return VAR;}
type     {adjust(); return TYPE;}

[a-zA-Z]+[a-zA-Z0-9|_]*     {adjust(); yylval.ival=String(yytext); return ID;}

