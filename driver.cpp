#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <iostream>
#include "lexer.h"
#include "parser.h"
#include "parse_tree_nodes.h"

using namespace std;

extern "C" {
    // Instantiate global variables
    extern FILE *yyin;     // input stream
    extern FILE *yyout;    // output stream
    extern int   yyleng;   // length of current lexeme
    extern char *yytext;   // text of current lexeme
    extern int   yylineno; // line number for current lexeme
    extern int   yylex();  // the generated lexical analyzer
}

// Needed global variables
extern int nextToken; // token returned from yylex

//*****************************************************************************
// The main processing loop
//
int main(int argc, char* argv[]) {
    bool printTree = true;
 // whether to print the parse tree
  ProgramNode* root = nullptr;
    // Set the input stream
    // Process any command-line switches
  for(int i = 1; i < argc; i++) {
    // -p flag: if requested, print while parsing
    if(strcmp(argv[i], "-p") == 0) {
      printParse = true;
    }
    // -t flag: if requested, print parse tree
    if(strcmp(argv[i], "-t") == 0) {
      printTree = true;
    }
    // -d flag: if requested, print while deleting parse tree
    if(strcmp(argv[i], "-d") == 0) {
      printDelete = true;
    }
    // -s flag: if requested, print mapTable
    if(strcmp(argv[i], "-s") == 0) {
      printSymbolMap = true;
    }
  }
    if (argc > 1) {
        printf("INFO: Using the %s file for input\n", argv[1]);
        yyin = fopen(argv[1], "r"); 
    }
  
    if (!yyin) {
        printf("ERROR: input file not found\n");
        return EXIT_FAILURE;
    }

    // Set the output stream
    yyout = stdout;

    // Get the first token
    nextToken = yylex();

    // Fire up the parser!
    try {
        // Process the expected production
        root = program();  
        //factor(); // Build bottom-up to <expression>
        //term();
        //simple_expression();
        //expression();

        if (nextToken != TOK_EOF)
            throw "end of file expected, but there is more here!";
        
    } catch (char const *errmsg) {
        cout << endl << "***ERROR:" << endl;
        cout << "On line number " << yylineno << ", near |" << yytext << "|, error type ";
        cout << errmsg << endl;
        return EXIT_FAILURE;
    }

    // Tell the world about our success!!
    cout << endl << "=== GO DAWGS! Your parse was successful! ===" << endl;


    if(printTree) {
    cout << endl << "*** Print the Tree ***" << endl ;
    cout << *root << endl;
  }

  cout << endl << "*** Interpret the Tree ***" << endl ;
  root->interpret();

  if (printSymbolMap){
    cout << endl << "*** User Defined Symbols ***" << endl << endl;
    for (const auto& pair : symbolMap) {
        cout << "First: " << pair.first << ", Second: " << pair.second << endl;
    }
  }

    /*// Print out the symbol table
    cout << endl << "*** User Defined Symbols ***" << endl << endl;
    set<string>::iterator it;
    for (it = symbolTable.begin(); it != symbolTable.end(); ++it) {
        cout << *it << endl;
    }*/

   cout << "*** Delete the Tree ***" << endl;
   if (printDelete){
   delete root;
   root = nullptr;
   }

    return EXIT_SUCCESS;
}

