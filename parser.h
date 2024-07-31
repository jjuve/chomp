#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <set>
#include <map>
#include <iostream>
#include "parse_tree_nodes.h"

using namespace std;

// Holds the symbols in the interpreted program
//extern set<string> symbolTable;
extern map<string, float> symbolMap;

extern int nextToken;        // next token returned by lexer

extern bool printParse;
extern bool printSymbolMap;

extern "C" {
	// Instantiate global variables used by flex
	extern int   yylex();      // the generated lexical analyzer
	extern char* yytext;       // text of current lexeme
	extern int   yylineno;
}

// Function declarations
ProgramNode* program();
//void factor();
//void term();
//void simple_expression();
//void expression();

#endif /* PARSER_H */
