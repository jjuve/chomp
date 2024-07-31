%option yylineno
%option noyywrap
%{
#include "lexer.h"

int line_number = 1;
%}

%%

 /* TOK_BEGIN */
"BEGIN" {return TOK_BEGIN;}

 /* TOK_BREAK */
"BREAK" {return TOK_BREAK;}

 /* TOK_CONTINUE */
"CONTINUE" {return TOK_CONTINUE;}

 /* TOK_DOWNTO */
"DOWNTO" {return TOK_DOWNTO;}

 /* TOK_ELSE */
"ELSE" {return TOK_ELSE;}

 /* TOK_END */
"END" {return TOK_END;}

 /* TOK_FOR */
"FOR" {return TOK_FOR;}

 /* TOK_IF */ 
"IF" {return TOK_IF;}

 /* TOK_LET */
"LET" {return TOK_LET;}

 /* TOK_PROGRAM */
"PROGRAM" {return TOK_PROGRAM;}

 /* TOK_READ */
"READ" {return TOK_READ;}

 /* TOK_THEN */
"THEN" {return TOK_THEN;}

 /* TOK_TO */
"TO" {return TOK_TO;}

 /* TOK_VAR */
"VAR" {return TOK_VAR;}

 /* TOK_WHILE */
"WHILE" {return TOK_WHILE;}

 /* TOK_WRITE */
"WRITE" {return TOK_WRITE;}

 /* TOK_INTEGER */
"INTEGER" {return TOK_INTEGER;}

 /* TOK_REAL */
"REAL" {return TOK_REAL;}

 /* TOK_SEMICOLON */
";" {return TOK_SEMICOLON;}

 /* TOK_COLON */
":" {return TOK_COLON;}

 /* TOK_OPENPAREN */
"(" {return TOK_OPENPAREN;}

 /* TOK_CLOSEPAREN */
")" {return TOK_CLOSEPAREN;}

 /* TOK_PLUS */
"+" {return TOK_PLUS;}

 /* TOK_MINUS */
"-" {return TOK_MINUS;}

 /* TOK_MULTIPLY */
"*" {return TOK_MULTIPLY;}

 /* TOK_DIVIDE */
"/" {return TOK_DIVIDE;}

 /* TOK_ASSIGN */
":=" {return TOK_ASSIGN;}

 /* TOK_EQUALTO */
"=" {return TOK_EQUALTO;}

 /* TOK_LESSTHAN */
"<" {return TOK_LESSTHAN;}

 /* TOK_GREATERTHAN */
">" {return TOK_GREATERTHAN;}

 /* TOK_NOTEQUALTO */
"<>" {return TOK_NOTEQUALTO;}

 /* TOK_MOD */
"MOD" {return TOK_MOD;}

 /* TOK_NOT */
"NOT" {return TOK_NOT;}

 /* TOK_OR */
"OR" {return TOK_OR;}

 /* TOK_AND */
"AND" {return TOK_AND;}

 /* TOK_IDENT */
[A-Z][A-Z0-9]{0,7} {return TOK_IDENT;}
[A-Z][A-Z0-9]{8,} {return TOK_UNKNOWN;}

 /* TOK_INTLIT */
[0-9]+ {return TOK_INTLIT;}

 /* TOK_FLOATLIT */
[0-9]+"."[0-9]+ {return TOK_FLOATLIT;}

 /* TOK_STRINGLIT */
'[^\n']{0,80}' {return TOK_STRINGLIT;}
'[^\n']{81,}' {return TOK_UNKNOWN;}
 
 /* Eating white space */
[ \t\r]+

 /* Newline */
\n {line_number++;}

 /* Ignoring comments */
"{".*"}"

 /* Found an unknown character */

.         { return TOK_UNKNOWN; }

 /* Recognize end of file */

<<EOF>>   { return TOK_EOF; }


