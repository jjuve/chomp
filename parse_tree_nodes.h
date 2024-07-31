#ifndef PARSE_TREE_NODES_H
#define PARSE_TREE_NODES_H

#include <iostream>
#include <vector>
#include <string>
#include "lexer.h"

using namespace std;

extern bool printDelete;      // shall we print deleting the tree?

//int level = 1;

// ---------------------------------------------------------------------
// Forward declaration of node types
class ProgramNode;
class BlockNode;
class Statementnode;
class FactorNode;
class AssignmentStmtNode;
class CompoundStmtNode;
class IfStmtNode;
class WhileStmtNode;
class ReadStmtNode;
class WriteStmtNode;
class ExpressionNode;
class SimpleExpNode;
class TermNode;
class IntLitNode;
class FloatlitNode;
class IdentNode;
class NotNode;
class MinusNode;
class NestNode;


////////////////////////////////////////////
class ProgramNode{
    public:
    int level = 0;
    BlockNode* block = nullptr;

    ProgramNode(int level, BlockNode* block);
    ~ProgramNode();
    void interpret();
};

ostream& operator<<(ostream&, ProgramNode&);

class BlockNode{
    public:
    int level = 0;
    CompoundStmtNode* compoundStmt = nullptr;

    BlockNode(int level, CompoundStmtNode* compoundStmt);
    ~BlockNode();
    void interpret();

};

ostream& operator<<(ostream&, BlockNode&);

class SimpleExpNode{
    public:
    int level = 0;
    TermNode* firstTermOps = nullptr;
    vector<int> restTermOps;
    vector<TermNode*> restTerm;

    SimpleExpNode(int level, TermNode* firstTerm);
    ~SimpleExpNode();
    float interpret();
};
ostream& operator<<(ostream&, SimpleExpNode&);

class ExpressionNode{
    public:
    int level = 0;
    SimpleExpNode* firstSimpleExp = nullptr;
    vector<int> restSimpleExp;
    vector<SimpleExpNode*> restSimple;

    ExpressionNode(int level, SimpleExpNode* firstSimpleExp);
    ~ExpressionNode();
    float interpret();
};

ostream& operator<<(ostream&, ExpressionNode&);

class TermNode{
    public:
    int level = 0;
    FactorNode* firstFactor = nullptr;
    vector<int> restFactorOps;
    vector<FactorNode*> restFactor;

    TermNode(int level, FactorNode* firstFactor);
    ~TermNode();
    float interpret();
};

ostream& operator<<(ostream&, TermNode&);

class StatementNode{
    public:
    int level = 0;
    virtual void printTo(ostream &os) = 0;
    virtual ~StatementNode();
    virtual void interpret() = 0 ;
};

ostream& operator<<(ostream&, StatementNode&);

class FactorNode{
    public:
    int level = 0 ;
    virtual void printTo(ostream &os) = 0;
    virtual ~FactorNode();
    virtual float interpret() = 0;
    
};

ostream& operator<<(ostream&, FactorNode&);

class AssignmentStmtNode : public StatementNode{
    public:
        string ident;
        ExpressionNode* expression = nullptr;

        AssignmentStmtNode(int level);
        ~AssignmentStmtNode();
        void printTo(ostream &os);
        void interpret();
};

class CompoundStmtNode : public StatementNode{
    public:
    vector<StatementNode*> statements;
    CompoundStmtNode(int level);
    ~CompoundStmtNode();
    void printTo(ostream &os);
    void interpret();
};

class IfStmtNode : public StatementNode{
    public:
    ExpressionNode* ifstatement = nullptr;
    StatementNode* thenstatement = nullptr;
    StatementNode* elsestatement = nullptr;

    IfStmtNode(int level);
    ~IfStmtNode();
    void printTo(ostream &os);
    void interpret();
};

class WhileStmtNode : public StatementNode{
    public:
    ExpressionNode* condition = nullptr;
    StatementNode* body = nullptr;
    
    WhileStmtNode(int level);
    ~WhileStmtNode();
    void printTo(ostream &os);
    void interpret();
};

class ReadStmtNode : public StatementNode{
    public:
    string var;

    ReadStmtNode(int level);
    ~ReadStmtNode();
    void printTo(ostream &os);
    void interpret();
};

class WriteStmtNode : public StatementNode{
    public:
    int type = 0;
    string content;

    WriteStmtNode(int level);
    ~WriteStmtNode();
    void printTo(ostream &os);
    void interpret();
};

class MinusNode : public FactorNode {
    public:
    FactorNode* factor = nullptr;

    MinusNode(int level, FactorNode* fn);
    ~MinusNode();
    void printTo(ostream &os);
    float interpret();
};

class NotNode : public FactorNode {
    public:
    FactorNode* factor = nullptr;

    NotNode(int level, FactorNode* fn);
    ~NotNode();
    void printTo(ostream &os);
    float interpret();
};

class NestNode : public FactorNode {
    public:
    ExpressionNode* expression = nullptr;

    NestNode(int level, ExpressionNode* en);
    ~NestNode();
    void printTo(ostream &os);
    float interpret();
};

class FloatLitNode : public FactorNode {
    public:
    double float_literal = 0;

    FloatLitNode(int level, float value);
    ~FloatLitNode();
    void printTo(ostream &os);
    float interpret();
};

class IdentNode : public FactorNode{
    public:
    string* idnet = nullptr;

    IdentNode(int level, string* name);
    ~IdentNode();
    void printTo(ostream &os);
    float interpret();
};

class IntLitNode : public FactorNode{
    public:
    int int_literal = 0;

    IntLitNode(int level, int value);
    ~IntLitNode();
    void printTo(ostream &os);
    float interpret();
};


#endif /* PARSE_TREE_NODES_H */
