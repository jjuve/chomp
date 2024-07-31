#include "parse_tree_nodes.h"
#include <map>

#define EPSILON 0.001
static bool truth(float F) {
return !((EPSILON > F) && (F > -EPSILON));
}

bool printDelete = false;   // shall we print deleting the tree?
map<string, float> symbolMap;
// ---------------------------------------------------------------------
// Indent according to tree level
static void indent(int level) {
  for (int i = 0; i < level; i++)
    cout << ("| ");
}
// ----------------------------------------------------------------------

//////////////Program//////////////////////////
ProgramNode::ProgramNode(int level, BlockNode* bn){
  level = 1 - 1;
  block = bn;
}
ProgramNode::~ProgramNode(){
  if(printDelete){
    cout << "Deleting ProgramNode" << endl;
    delete block; block = nullptr;
  }
}
ostream& operator<<(ostream& os, ProgramNode& pn){
  os << endl; indent(pn.level); os << "(program ";
  os << *pn.block;
  os << endl; indent(pn.level); os << "program) " << endl;
  return os;
}
void ProgramNode::interpret()
{
block->interpret();
}

///////////////BlockNode///////////
BlockNode::BlockNode(int l, CompoundStmtNode* cs){
  level = l - 1;
  this->compoundStmt=cs;
}
BlockNode::~BlockNode() {
    if(printDelete) {
        cout << "Deleting BlockStmtNode" << endl;
    }
    delete compoundStmt; compoundStmt = nullptr;
}
ostream& operator<<(ostream& os, BlockNode& bn){
  os << endl; indent(bn.level); os << "(block ";
  os << *bn.compoundStmt;
  os << endl; indent(bn.level); os << " block)";
  return os;
}
void BlockNode::interpret()
{
compoundStmt->interpret();
}

//////////////Statement//////////////////////
StatementNode::~StatementNode(){}
ostream& operator<<(ostream& os, StatementNode& sn){
  sn.printTo(os);
  return os;
}
void StatementNode::interpret(){
  this->interpret();
} 
////////Factor node////////////////////
FactorNode::~FactorNode(){}
ostream& operator<<(ostream& os, FactorNode& fn){
  fn.printTo(os);
  return os;
} 
float FactorNode::interpret(){
  return this->interpret();
} 

//////////////////Assignment///////////////////////
AssignmentStmtNode::AssignmentStmtNode(int l){
  level =  l - 1;
}
AssignmentStmtNode::~AssignmentStmtNode(){
  if(printDelete){
    cout << "Deleting StatementNode::AssignmentStmtNode" << endl;
    delete expression; expression = nullptr;
  }
}
void AssignmentStmtNode::printTo(ostream& os){
  os << endl; indent(level); os << "(assignment_stmt ";
  os << "( "; os << ident; os << " := ) "; os << *expression;
  os << endl; indent(level); os << "assignment_stmt) ";
}
void AssignmentStmtNode::interpret()
{
// Look up the variable that will store expression result
map<string, float>::iterator variable = symbolMap.find(ident);
// Put the expression in the variable
variable->second = expression->interpret();
}


////////////////////////CompoundStmt//////////////////////////////////
CompoundStmtNode::CompoundStmtNode(int l){
  level = l - 1;
}
CompoundStmtNode::~CompoundStmtNode(){
  if(printDelete){
    cout << "Deleting StatementNode::CompoundStmtNode" << endl;
    int length = statements.size();
    for(int i = 0; i < length; i++){
      delete statements[i];
    }
    statements.clear();
  }
}
void CompoundStmtNode::printTo(ostream& os){
  os << endl; indent(level); os << "(compound_stmt ";
  int length = statements.size();
  for(int i = 0; i < length; i++){
    os << *statements[i];
  }
  os << endl; indent(level); os << "compound_stmt) "; 
}
void CompoundStmtNode::interpret(){
  for (auto* iter : statements) { 
        iter ->interpret();
    }
}

/////////////////////////////IfStmt//////////////////////////////////
IfStmtNode::IfStmtNode(int l){
  level = l - 1;
}
IfStmtNode::~IfStmtNode(){
  if(printDelete){
    cout << "Deleting StatementNode::IfStmtNode" << endl;
    delete ifstatement; ifstatement = nullptr;
    delete thenstatement; thenstatement = nullptr;
    delete elsestatement; elsestatement = nullptr;
  }
}
void IfStmtNode::printTo(ostream& os){
  os << endl; indent(level); os << "(if_stmt ";
  os << *ifstatement;
 

  os << endl; indent(level); os << "(then  ";
  os << *thenstatement;
  os << endl; indent(level); os << "then)  ";

  if (elsestatement != nullptr){
    os << endl; indent(level); os << "(else ";
    os << *elsestatement;
    os << endl; indent(level); os << "else) ";
  }

  os << endl; indent(level); os << "if_stmt)  ";

}
void IfStmtNode::interpret() {
    float conditionValue = ifstatement->interpret();

    if (truth(conditionValue)) {
        if (thenstatement != nullptr) {
            thenstatement->interpret();
        }
    } else {
        if (elsestatement != nullptr) {
            elsestatement->interpret();
        }
    }
}

////////////////////////WhileStmt////////////////////////////
WhileStmtNode::WhileStmtNode(int l){
  level = l - 1;
}
WhileStmtNode::~WhileStmtNode() {
    if (printDelete) {
        std::cout << "Deleting WhileStmtNode" << std::endl;
    }
    delete condition; condition = nullptr;
    delete body; body = nullptr;
}
void WhileStmtNode::printTo(ostream& os) {
    os << endl; indent(level); os << "(while_stmt ";
    os << *condition;

    os << *body;
    os << ")" << endl; indent(level); os << "while_stmt)";
}
void WhileStmtNode::interpret() {
    while (truth(condition->interpret())) {
        if (body != nullptr) {
            body->interpret();
        }
    }
}

///////////////////ReadStmt////////////////
ReadStmtNode::ReadStmtNode(int l){
  level = l - 1;
  }
ReadStmtNode::~ReadStmtNode() {
    if(printDelete){
        cout << "Deleting ReadStmtNode" << endl;
    }
}
void ReadStmtNode::printTo(ostream& os){
    os << endl; indent(level); os << "(read_stmt "; os << "( ";
    os << var;
    os << " )" << endl; indent(level); os << "read_stmt)";
}
void ReadStmtNode::interpret() {
    float inputValue;
    cout << "Enter value for " << var << ": ";
    cin >> inputValue;

    symbolMap[var] = inputValue;
}

///////////////////WriteStm////////////////////////
WriteStmtNode::WriteStmtNode(int l){
  level = l - 1;
}
WriteStmtNode::~WriteStmtNode() {
    if(printDelete){
        cout << "Deleting WriteStmtNode" << endl;
    }
}
void WriteStmtNode::printTo(ostream& os){
    os << endl; indent(level); os << "(write_stmt "; os << "( ";
    os << content;
    os << " )";  
    
    os << endl; indent(level); os << "write_stmt)";
}
void WriteStmtNode::interpret()
{
// Implement the write statement, depending on what is being written
switch(type) {
case TOK_STRINGLIT:
// If we are writing a string, write it. First, strip
// leading and trailing quote characters.
cout << content.substr(1, content.length()-2) << endl;
break;
case TOK_IDENT:
// If we are writing a variable, look up and print value
//symbolTableT::iterator variable = symbolTable.find(content);
map<string, float>::iterator variable = symbolMap.find(content);
cout << variable->second << endl;
break;
}
}

//////////ExpressionNode///////////////////
ExpressionNode::ExpressionNode(int l, SimpleExpNode* firstSimpleExp)
{
level = l - 1;
this->firstSimpleExp = firstSimpleExp;
}
ExpressionNode::~ExpressionNode() {
    if(printDelete) {
        cout << "Deleting ExpressionNode" << endl;
    }
    delete firstSimpleExp; firstSimpleExp = nullptr;
    for (auto* exp : restSimple) { 
        delete exp; exp = nullptr;
    }
    
}
ostream& operator <<(ostream& os, ExpressionNode& en){
  os << endl; indent(en.level); os << "(expression ";
  os << *(en.firstSimpleExp);
  for (int i = 0; i < en.restSimpleExp.size(); i++){
    switch (en.restSimpleExp[i])
    {
    case TOK_EQUALTO:
      os << endl; indent(en.level); os << "=";
      break;
    case TOK_LESSTHAN:
      os << endl; indent(en.level); os << "<";
      break;
    case TOK_GREATERTHAN:
      os << endl; indent(en.level); os << ">";
      break;
    case TOK_NOTEQUALTO:
      os << endl; indent(en.level); os << "<>";
      break;
    }
    os << *(en.restSimple[i]);
  }
    
    os << endl; indent(en.level); os << " expression)";
    return os;
}
float ExpressionNode::interpret() {

    float result = firstSimpleExp->interpret();

    for (int i = 0; i < restSimple.size(); i++) {
        float nextResult = restSimple[i]->interpret();

        switch (restSimpleExp[i]) {
            case TOK_EQUALTO:
                result = truth(result - nextResult) ? 0.0f : 1.0f;
                break;
            case TOK_LESSTHAN:
                result = (result < nextResult) ? 1.0f : 0.0f;
                break;
            case TOK_GREATERTHAN:
                result = (result > nextResult) ? 1.0f : 0.0f;
                break;
            case TOK_NOTEQUALTO:
                result = truth(result - nextResult) ? 1.0f : 0.0f;
                break;
            default:
                break;
        }

        
        if (!truth(result)) break; 
    }

    return result;
}

/////////////////simpleExpression/////////////////////
SimpleExpNode::SimpleExpNode(int l, TermNode* firstTermOps){
  level = l - 1;
  this->firstTermOps = firstTermOps;
}
SimpleExpNode::~SimpleExpNode() {
    if(printDelete) {
        cout << "Deleting SimpleExpNode" << endl;
    }
    delete firstTermOps; firstTermOps = nullptr;
    for (auto* simp : restTerm) { 
        delete simp; simp = nullptr;
    }
}
ostream& operator <<(ostream& os, SimpleExpNode& sn){
  os << endl; indent(sn.level); os << "(simple_exp ";
  os << *(sn.firstTermOps);
  for (int i = 0; i < sn.restTermOps.size(); i++){
    switch (sn.restTermOps[i])
    {
    case TOK_PLUS:
      os << endl; indent(sn.level); os << "+";
      break;
    case TOK_MINUS:
      os << endl; indent(sn.level); os << "-";
      break;
    case TOK_OR:
      os << endl; indent(sn.level); os << "OR";
      break;
    }
    os << *(sn.restTerm[i]);
  }
    os << endl; indent(sn.level); os << " simple_exp)";
    return os;
}
float SimpleExpNode::interpret() {
    float result = firstTermOps->interpret();

    for (int i = 0; i < restTerm.size(); i++) {
        float nextTermResult = restTerm[i]->interpret();

        switch (restTermOps[i]) {
            case TOK_PLUS:
                result += nextTermResult;
                break;
            case TOK_MINUS:
                result -= nextTermResult;
                break;
            case TOK_OR:
                result = (result != 0 || nextTermResult != 0) ? 1.0f : 0.0f;
                break;
            default:
                break;
        }
    }

    return result;
}


////////////////termNode//////////////////////
TermNode::TermNode(int l, FactorNode* firstFactor){
  level = l - 1;
  this->firstFactor = firstFactor;
}
TermNode::~TermNode() {
    if(printDelete) {
        cout << "Deleting TermNode " <<  endl;
    }
    delete firstFactor; firstFactor = nullptr;
    for (auto* expr : restFactor) { 
        delete expr; expr = nullptr;
    }
}
ostream& operator<<(ostream& os, TermNode& tn) {
    os << endl; indent(tn.level); os << "(term ";
    if (tn.firstFactor != nullptr) {
        os << *(tn.firstFactor);  
    }
    for (int i = 0; i < tn.restFactorOps.size(); i++) {
        os << " ";
        switch (tn.restFactorOps[i]) {
            case TOK_MULTIPLY:
                os << endl; indent(tn.level); os << "* ";
                break;
            case TOK_DIVIDE:
                os << endl; indent(tn.level); os << "/ ";
                break;
            case TOK_AND:
                os << endl; indent(tn.level); os << "AND ";
                break;
            default:
                os << "OP ";
                break;
        }
        if (i < tn.restFactor.size() && tn.restFactor[i] != nullptr) {
            os << *(tn.restFactor[i]);  
        }
        
    }
    os << endl; indent(tn.level); os << "term)";
    return os;
}
float TermNode::interpret() {
    float result = firstFactor->interpret();

    for (int i = 0; i < restFactor.size(); i++) {
        float nextFactorResult = restFactor[i]->interpret();

        switch (restFactorOps[i]) {
            case TOK_MULTIPLY:
                result *= nextFactorResult;
                break;
            case TOK_DIVIDE:
                if (nextFactorResult == 0) {
                    return 0; 
                }
                result /= nextFactorResult;
                break;
            case TOK_AND:
                result = (result != 0 && nextFactorResult != 0) ? 1 : 0;
                break;
            default:
                break;
        }
    }

    return result;
}


////////////////IntLitNode//////////////////
IntLitNode::IntLitNode(int l, int value){
  level = l - 1;
  int val;
  this->int_literal = value;
}
IntLitNode::~IntLitNode() {
    if(printDelete) {
        cout << "Deleting IntLitNode with value: " << int_literal << endl;
    }
}
void IntLitNode::printTo(ostream& os){
  os << endl; indent(level);
  os << " (factor ( INTLIT: " << int_literal << " )"; 
  os << endl;indent(level); os << " factor)"; 

}
float IntLitNode::interpret() {
    return static_cast<float>(int_literal);
}

////////////////FloatLitNode//////////////////
FloatLitNode::FloatLitNode(int l, float value){
  level = l - 1;
  this->float_literal= value;
}
FloatLitNode::~FloatLitNode() {
    if(printDelete) {
        cout << "Deleting FloatLitNode with value: " << float_literal << endl;
    }
}
void FloatLitNode::printTo(ostream& os){
  
  os << endl;indent(level);
  os << " (factor ( FLOATLIT: " << float_literal << " )";
  os << endl;indent(level); os << " factor)";

}
float FloatLitNode::interpret() {
    return float_literal;
}

////////////IdentLit/////////////////////
IdentNode::IdentNode(int l, string* identifier){
level = l - 1;
this->idnet = identifier;
}
IdentNode::~IdentNode() {
    if(printDelete) {
        cout << "Deleting IdentNode with identifier: " << idnet << endl;
    }
  delete idnet;
}
void IdentNode::printTo(ostream& os){
  os << endl; indent(level);
  os << " (factor ( IDENT: " << *idnet << " )"; 
  os << endl;indent(level); os << " factor)";
}
float IdentNode::interpret() {
    auto it = symbolMap.find(*idnet);
    if (it != symbolMap.end()) {
        return it->second;
    } else {
        return 0.0f;
    }
}


///////////////NotNode/////////////////
NotNode::NotNode(int l, FactorNode* fn){
  level = l - 1;
  this->factor = fn;
}
NotNode::~NotNode() {
    if(printDelete) {
        cout << "Deleting NotNode" << endl;
    }
    delete factor; factor = nullptr;
}
void NotNode::printTo(ostream& os){
  os << endl;indent(level);
  os << " (factor (NOT " << *factor << " )"; 
  os << endl;indent(level); os << " factor)";
}
float NotNode::interpret() {
    if (factor != nullptr) {
        float result = factor->interpret();
        return (result == 0.0f) ? 1.0f : 0.0f;
    }

    return 1.0f;
}

//////////////////MinusNode///////////////////
MinusNode::MinusNode(int l, FactorNode* mn){
  level = l - 1;
  this->factor = mn;
}
MinusNode::~MinusNode() {
    if(printDelete) {
        cout << "Deleting MinusNode" << endl;
    }
    delete factor; factor = nullptr;
}
void MinusNode::printTo(ostream& os) {
  os << endl;indent(level);
  os << " (factor (- " << *factor << " )"; 
  os << endl;indent(level); os << " factor)";
  
}
float MinusNode::interpret() {
    if (factor != nullptr) {
        return -factor->interpret();
    }

    return 0.0f;
}

///////////////nestNode/////////////////
NestNode::NestNode(int l, ExpressionNode* nn){
level = l - 1;
this->expression=nn;
}
NestNode::~NestNode(){
  if(printDelete){
    cout << "Deleting NestNode" << endl;
  }
  delete expression; expression = nullptr;
}
void NestNode::printTo(ostream& os) {
  os << endl; indent(level); os << "factor (";
    os << *expression;
    os << endl;indent(level); os << " factor)";
}
float NestNode::interpret() {
    if (expression != nullptr) {
        return expression->interpret();
    }

    return 0.0f;
}

