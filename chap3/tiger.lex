%{
/* C declarations: */
#include <string.h>
#include "util.h"
#include "y.tab.h"
#include "errormsg.h"

int charPos=1;

int yywrap(void) {
	charPos=1;
	return 1;
}

void adjust(void){
	EM_tokPos=charPos;
	charPos+=yyleng;
}

char* edit_string(void){
	yytext[yyleng-1] = '\0';
	yytext += 1;
	return yytext;
}


%}



%Start COMMENT STRING_STA
%%
 /* Regular Expressions and Actions */
<INITIAL>","						{adjust(); return COMMA;}
<INITIAL>":"						{adjust(); return COLON;}
<INITIAL>";"						{adjust(); return SEMICOLON;}
<INITIAL>\(							{adjust(); return LPAREN;}
<INITIAL>\)							{adjust(); return RPAREN;}
<INITIAL>"["						{adjust(); return LBRACK;}
<INITIAL>"]"						{adjust(); return RBRACK;}
<INITIAL>"{"						{adjust(); return LBRACE;}
<INITIAL>"}"						{adjust(); return RBRACE;}
<INITIAL>"."						{adjust(); return DOT;}
<INITIAL>"+"						{adjust(); return PLUS;}
<INITIAL>"-"						{adjust(); return MINUS;}
<INITIAL>"*"						{adjust(); return TIMES;}
<INITIAL>"/"						{adjust(); return DIVIDE;}
<INITIAL>"="						{adjust(); return EQ;}
<INITIAL>"<>"						{adjust(); return NEQ;}
<INITIAL>"<"						{adjust(); return LT;}
<INITIAL>"<="						{adjust(); return LE;}
<INITIAL>">"						{adjust(); return GT;}
<INITIAL>">="						{adjust(); return GE;}
<INITIAL>"&"						{adjust(); return AND;}
<INITIAL>"|"						{adjust(); return OR;}
<INITIAL>":="						{adjust(); return ASSIGN;}

 /* Reseverd words */
<INITIAL>array						{adjust(); return ARRAY;}
<INITIAL>if							{adjust(); return IF;}
<INITIAL>then						{adjust(); return THEN;}
<INITIAL>else						{adjust(); return ELSE;}
<INITIAL>while						{adjust(); return WHILE;}
<INITIAL>for						{adjust(); return FOR;}
<INITIAL>to							{adjust(); return TO;}
<INITIAL>do							{adjust(); return DO;}
<INITIAL>let						{adjust(); return LET;}
<INITIAL>in							{adjust(); return IN;}
<INITIAL>end						{adjust(); return END;}
<INITIAL>of							{adjust(); return OF;}
<INITIAL>break						{adjust(); return BREAK;}
<INITIAL>nil						{adjust(); return NIL;}
<INITIAL>function					{adjust(); return FUNCTION;}
<INITIAL>var						{adjust(); return VAR;}
<INITIAL>type						{adjust(); return TYPE;}

 /* Comments*/
<INITIAL>"/*"						{adjust(); BEGIN COMMENT;}
<COMMENT>"*/"						{adjust(); BEGIN INITIAL;}
<COMMENT>.							{adjust(); continue;}

<INITIAL>" "						{adjust(); continue;}
\t									{adjust(); continue;}
\n									{adjust(); EM_newline(); continue;}
\r									{adjust(); continue;}

 /* Strings, allow \", \\, \n, \r, \t inside a string, but do not allow \ appears alone */
<INITIAL>\"((\\\")*(\\\\)*(\\n)*(\\r)*(\\t)*[^\"\n\r\\]*)*\"	{
	adjust(); yylval.sval=edit_string(); return STRING;
}
<INITIAL>[a-zA-Z][a-zA-Z0-9"_"]*	{adjust(); yylval.sval=yytext; return ID;}

<INITIAL>[0-9]+						{adjust(); yylval.ival=atoi(yytext); return INT;}

.	 								{adjust(); EM_error(EM_tokPos,"illegal token");}
