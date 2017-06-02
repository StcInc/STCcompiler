#ifndef NODE_H
#define NODE_H

#include <vector>
#include <string>
#include <iostream>
#include "nodevalue.h"


#define LOG(Mess) (std::cout << Mess << std::endl)



/* Standard types */
enum MyBasicType {
    T_VOID = 0,
    T_INT,
    T_CHAR,
    T_FLOAT,
    T_BOOL,
    T_STRING
};

enum Commands {
    C_NOOP, // for non comands
    C_ASG,
    C_VARDECL,
    C_IF,
    C_FOR,
    C_WHILE,
    C_POST,
    C_FCALL,
    C_RETURN,
    C_BREAK,
    C_CONTINUE,
    C_INC,
    C_BLOCK
};


class ArgList;
class Arg;
class Assignment;
class BinaryExpr;

class ArrayDim;
class Command;
class Break;
class Continue;
class Conditional;
class Declaration;
class ArrayItems;
class Indexing;

class ParamList;

class LeftPartExpr;
class DoLoop;
class Expression;

class FunctionCall;
class FunctionDecl;
class Identifier;
class Literal;
class Increment;
class Loop;

class OperatorBlock;
class Program;
class Return;
class TypeNode;
class UnaryExpr;

class VariableDecl;
class WhileLoop;
class ForLoop;
class PostLoop;
class ForInit;


class OtherDeclarations;

/******************************************************************************/
/******************              IMPLEMENTATION              ******************/
/******************************************************************************/

class Node {
public:
    NodeValue * value;
    std::vector<Node*> children;

    Node () {
        value = NULL;
    }

    Node (NodeValue * nodeValue) {
        value = nodeValue;
    }

    virtual ~Node() {
        for (int i = 0; i < this->children.size(); ++i) {
            delete this->children[i];
        }
        delete value;

    }

    virtual void print(int level = 0) {
        printWhitespaces(level);
        std::cout << getClassName();
        if (value) {
            std::cout << ": " << value->getValue();
        }
        std::cout << std::endl;
        for (int i = 0; i < this->children.size(); ++i) {
            if (this->children[i]) {
                this->children[i]->print(level+1);
            }

        }
    }

    void printWhitespaces(int level) {
        for (int i = 0; i < level; ++i) {
            std::cout << "    ";
        }
    }

    void addChild(Node * child) {
        children.push_back(child);
    }

    virtual std::string getClassName() = 0;
    virtual Commands getCommand () = 0;
    virtual void flatten() = 0;

};

class ArrayDim : public Node {
public:
    ArrayDim () {

    }

    ArrayDim (NodeValue * nodeValue) : Node(nodeValue) {

    }

    std::string getClassName() {
        return "ArrayDim";
    }

    Commands getCommand () {
        return C_NOOP;
    }

    void flatten() {
        if (this->children[0]) {
            this->children[0]->flatten();
        }
        else {
            LOG(getClassName() + "->children[0] is null");
        }
        ArrayDim * iter = (ArrayDim *) this->children[1];
        ArrayDim * tmp;
        this->children.pop_back();
        while (iter) {
            tmp = iter;
            if (iter->children[0]) {
                iter->children[0]->flatten();
                this->children.push_back(iter->children[0]);
            }
            else {
                LOG(iter->getClassName() + "->children[0] is null");
            }
            iter = (ArrayDim *) iter->children[1];
            tmp->children.clear();
            delete tmp;
        }
    }


};

class OtherDeclarations : public Node {
public:
    OtherDeclarations () {

    }

    OtherDeclarations (NodeValue * nodeValue) : Node(nodeValue) {

    }

    std::string getClassName() {
        return "OtherDeclarations";
    }

    Commands getCommand () {
        return C_NOOP;
    }

    void flatten() {
        // will be flattened in Program call
    }
};

class TypeNode : public Node {
public:
    MyBasicType type;

    TypeNode () {

    }

    TypeNode (NodeValue * nodeValue) : Node(nodeValue) {

    }

    TypeNode(MyBasicType t) {
        type = t;
    }

    std::string typeToStr(MyBasicType type) {
        switch (type) {
            case T_VOID:   return std::string("VOID");
            case T_INT:    return std::string("INT");
            case T_CHAR:   return std::string("CHAR");
            case T_FLOAT:  return std::string("FLOAT");
            case T_BOOL:   return std::string("BOOL");
            case T_STRING: return std::string("STRING");
            default:       return std::string("VOID");
        }
    }

    void print(int level = 0) {
        printWhitespaces(level);
        std::cout << getClassName() << ": " << typeToStr(type) << std::endl;
    }

    std::string getClassName() {
        return "TypeNode";
    }

    Commands getCommand () {
        return C_NOOP;
    }

    void flatten() {
    }
};

class Command : public Node {
public:
    Command () {

    }

    Command (NodeValue * nodeValue) : Node(nodeValue) {

    }

    virtual std::string getClassName() = 0;
    virtual Commands getCommand () = 0;
    virtual void flatten() = 0;
};

class Break : public Command {
public:
    Break () {

    }

    Break (NodeValue * nodeValue) : Command(nodeValue) {

    }
    std::string getClassName() {
        return "Break";
    }

    Commands getCommand () {
        return C_BREAK;
    }


    void flatten() {
    }
};

class Continue : public Command {
public:
    Continue () {

    }

    Continue (NodeValue * nodeValue) : Command(nodeValue) {

    }
    std::string getClassName() {
        return "Continue";
    }

    Commands getCommand () {
        return C_CONTINUE;
    }

    void flatten() {
    }
};

class Expression: public Command {
public:
    Expression () {

    }

    Expression (NodeValue * nodeValue) : Command(nodeValue) {

    }

    virtual std::string getClassName() = 0;
    virtual Commands getCommand () = 0;
    virtual void flatten() = 0;
};

class Program : public Node { // [Declaration, Program]
public:
    Program () {

    }

    Program (NodeValue * nodeValue) : Node(nodeValue) {

    }

    std::string getClassName() {
        return "Program";
    }

    Commands getCommand () {
        return C_NOOP;
    }

    void flatten() {
        if (this->children[0]) {
            this->children[0]->flatten();
        }
        else {
            LOG(getClassName() + "->children[0] is null");
        }
        Program * iter = (Program *) this->children[1];
        Program * tmp;
        this->children.pop_back();
        while (iter) {
            tmp = iter;
            if (iter->children[0]) {
                iter->children[0]->flatten();
                this->children.push_back(iter->children[0]);
            }
            else {
                LOG(iter->getClassName() + "->children[0] is null");
            }
            iter = (Program *)iter->children[1];
            tmp->children.clear();
            delete tmp;
        }

    }

};

class ArrayItems : public Expression {
public:
    ArrayItems () {

    }

    ArrayItems (NodeValue * nodeValue) : Expression(nodeValue) {

    }

    std::string getClassName() {
        return "ArrayItems";
    }

    Commands getCommand () {
        return C_NOOP;
    }

    void flatten() {
        if (this->children[0]) {
            this->children[0]->flatten();
        }
        else {
            LOG(getClassName() + "->children[0] is null");
        }
        ArrayItems * iter = (ArrayItems *) this->children[1];
        ArrayItems * tmp;
        this->children.pop_back();
        while (iter) {
            tmp = iter;
            if (iter->children[0]) {
                iter->children[0]->flatten();
                this->children.push_back(iter->children[0]);
            }
            else {
                LOG(iter->getClassName() + "->children[0] is null");
            }
            iter = (ArrayItems *) iter->children[1];
            tmp->children.clear();
            delete tmp;
        }
    }
};

class Indexing : public Node {
public:
    Indexing () {

    }

    Indexing (NodeValue * nodeValue) : Node(nodeValue) {

    }

    std::string getClassName() {
        return "Indexing";
    }

    Commands getCommand () {
        return C_NOOP;
    }

    void flatten() {
        if (this->children[0]) {
            this->children[0]->flatten(); // expression in brackets
        }
        else {
            LOG(getClassName() + "->children[0] is null");
        }

        Indexing * iter = (Indexing *)this->children[1]; // another Indexing Object
        Indexing * tmp;
        this->children.pop_back();

        while (iter) {
            tmp = iter;
            if (iter->children[0]) {
                iter->children[0]->flatten(); // expression in brackets
                this->children.push_back(iter->children[0]);
            }
            else {
                LOG(iter->getClassName() + "->children[0] is null");
            }
            iter = (Indexing *)iter->children[1];
            tmp->children.clear();
            delete tmp;
        }
    }
};


class LeftPartExpr : public Node {
public:
    LeftPartExpr () {

    }

    LeftPartExpr (NodeValue * nodeValue) : Node(nodeValue) { //[id, Indexing]

    }

    std::string getClassName() {
        return "LeftPartExpr";
    }

    Commands getCommand () {
        return C_NOOP;
    }

    void flatten() {
        Indexing * iter = (Indexing *) this->children[1];
        this->children.pop_back();
        Indexing * tmp;
        while (iter) {
            tmp = iter;
            this->children.push_back(iter->children[0]);
            iter = (Indexing *) iter->children[1];
            tmp->children.clear();
            delete tmp;
        }
    }
};

class ArgList : public Node { // [Arg, ArgList]
public:
    ArgList () {

    }

    ArgList (NodeValue * nodeValue) : Node(nodeValue) {

    }

    std::string getClassName() {
        return "ArgList";
    }

    Commands getCommand () {
        return C_NOOP;
    }

    void flatten() {
        if (this->children[0]) {
            this->children[0]->flatten();
        }
        else {
            LOG(getClassName() + "->children[0] is null");
        }
        ArgList * iter = (ArgList *) this->children[1];
        ArgList * tmp;
        this->children.pop_back();
        while (iter) {
            tmp = iter;
            if (iter->children[0]) {
                iter->children[0]->flatten();
                this->children.push_back(iter->children[0]);
            }
            else {
                LOG(iter->getClassName() + "->children[0] is null");
            }
            iter = (ArgList *)iter->children[1];
            tmp->children.clear();
            delete tmp;
        }
    }

};

class Arg : public Node {
public:
    Arg () {

    }
    Arg (NodeValue * nodeValue) : Node(nodeValue) {

    }

    std::string getClassName() {
        return "Arg";
    }

    Commands getCommand () {
        return C_NOOP;
    }

    void flatten() {
    }
};

class ParamList : public Node {
public:
    ParamList () {

    }

    ParamList (NodeValue * nodeValue) : Node(nodeValue) { // [rightPartExpr, ParamList]

    }

    std::string getClassName() {
        return "ParamList";
    }

    Commands getCommand () {
        return C_NOOP;
    }

    void flatten() {
        if (this->children[0]) {
            this->children[0]->flatten(); // rightPartExpr
        }
        else {
            LOG(getClassName() + "->children[0] is null");
        }
        ParamList * iter = (ParamList *) this->children[1];
        ParamList * tmp;
        this->children.pop_back();
        while (iter) {
            tmp = iter;
            if (iter->children[0]) {
                iter->children[0]->flatten(); // rightPartExpr
                this->children.push_back(iter->children[0]);
            } else {
                LOG(iter->getClassName() + "->children[0] is null");
            }
            iter = (ParamList *) iter->children[1];
            tmp->children.clear();
            delete tmp;
        }
    }
};


class Assignment: public Command { // [LeftPartExpr, Expression/ArrayItems/condition/Literal]
public:
    Assignment () {

    }

    Assignment (NodeValue * nodeValue) : Command(nodeValue) {

    }

    std::string getClassName() {
        return "Assignment";
    }

    Commands getCommand () {
        return C_ASG;
    }

    void flatten() {
        if (this->children[0]) {
            this->children[0]->flatten(); // LeftPartExpr
        }
        else {
            LOG(getClassName() + "->children[0] is null");
        }
        if (this->children[1]) {
            this->children[1]->flatten(); // Expression
        }
        else {
            LOG(getClassName() + "->children[1] is null");
        }
    }
};


class Conditional: public Command { // []
public:
    Conditional () {

    }

    Conditional (NodeValue * nodeValue) : Command(nodeValue) {

    }

    std::string getClassName() {
        return "Conditional";
    }

    Commands getCommand () {
        return C_IF;
    }

    void flatten() {
        if (this->children[0]) {
            this->children[0]->flatten(); // Condition
        }
        else {
            LOG(getClassName() + "->children[0] is null");
        }
        if (this->children[1]) {
            this->children[1]->flatten(); // OperatorBlock
        }
        else {
            LOG(getClassName() + "->children[1] is null");
        }
        if (this->children[2]) {
            this->children[2]->flatten(); // OperatorBlock or another Conditional object may be absent
        }
    }
};

class Declaration : public Node {
public:
    Declaration () {

    }

    Declaration (NodeValue * nodeValue) : Node(nodeValue) {

    }

    virtual std::string getClassName() = 0;
    virtual Commands getCommand () = 0;
    virtual void flatten() = 0;
};


class Loop: public Command {
public:
    Loop () {

    }

    Loop (NodeValue * nodeValue) : Command(nodeValue) {

    }

    virtual std::string getClassName() = 0;
    virtual Commands getCommand () = 0;
    virtual void flatten() = 0;
};

class BinaryExpr: public Expression { // [Expression, Expression]
public:
    BinaryExpr () {

    }

    BinaryExpr (NodeValue * nodeValue) : Expression(nodeValue) {

    }
    std::string getClassName() {
        return "BinaryExpr";
    }

    Commands getCommand () {
        return C_NOOP;
    }

    void flatten() {
        if (this->children[0]) {
            this->children[0]->flatten(); // Expression
        }
        else {
            LOG(getClassName() + "children[0] is null");
        }
        if (this->children[1]) {
            this->children[1]->flatten(); // Expression
        }
        else {
            LOG(getClassName() + "->children[1] is null");
        }
    }

};

class ForLoop: public Loop { //[forInit, body]
public:
    ForLoop () {

    }

    ForLoop (NodeValue * nodeValue) : Loop(nodeValue) {

    }

    std::string getClassName() {
        return "ForLoop";
    }

    Commands getCommand () {
        return C_FOR;
    }

    void flatten() {
        if (this->children[0]) {
            this->children[0]->flatten(); // ForInit
        }
        else {
            LOG(getClassName() + "->children[0] is null");
        }
        if (this->children[1]) {
            this->children[1]->flatten(); // OperatorBlock
        }
        else {
            LOG(getClassName() + "->children[1] is null");
        }
    }
};

class ForInit : public Node { //[var_decl, condition, Expression]
public:
    ForInit () {

    }

    ForInit (NodeValue * nodeValue) : Node(nodeValue) {

    }

    std::string getClassName() {
        return "ForInit";
    }

    Commands getCommand () {
        return C_NOOP;
    }

    void flatten() {
        if (this->children[0]) {
            this->children[0]->flatten(); // VariableDecl
        }
        else {
            LOG(getClassName() + "->children[0] is null");
        }
        if (this->children[1]) {
            this->children[1]->flatten(); // Condition
        }
        else {
            LOG(getClassName() + "->children[1] is null");
        }
        if (this->children[2]) {
            this->children[2]->flatten(); // Expression !!!!!!!!!
            //TODO: think over whether there should be an expression in for's header or a command
        }
        else {
            LOG(getClassName() + "->children[2] is null");
        }
    }
};

class PostLoop : public Loop { // [body, condition]
public:
    PostLoop () {

    }

    PostLoop (NodeValue * nodeValue) : Loop(nodeValue) {

    }

    std::string getClassName() {
        return "PostLoop";
    }

    Commands getCommand () {
        return C_POST;
    }

    void flatten() {
        if (this->children[0]) {
            this->children[0]->flatten(); // OperatorBlock
        }
        else {
            LOG(getClassName() + "->children[0] is null");
        }
        if (this->children[1]) {
            this->children[1]->flatten(); // Condition
        }
        else {
            LOG(getClassName() + "->children[1] is null");
        }
    }
};

class FunctionCall: public Expression { // [name, params]
public:
    FunctionCall () {

    }

    FunctionCall (NodeValue * nodeValue) : Expression(nodeValue) {

    }
    std::string getClassName() {
        return "FunctionCall";
    }

    Commands getCommand () {
        return C_FCALL;
    }

    void flatten() {
        if (this->children[1]) {
            this->children[1]->flatten(); // ParamList
        }
        else {
            LOG(getClassName() + "->children[1] is null");
        }
    }
};

class FunctionDecl: public Declaration { // [type, name, args, body]
public:
    FunctionDecl () {

    }

    FunctionDecl (NodeValue * nodeValue) : Declaration(nodeValue) {

    }
    std::string getClassName() {
        return "FunctionDecl";
    }

    Commands getCommand () {
        return C_NOOP;
    }

    bool isPredefinition() {
        return this->children[3];
    }

    void flatten() {
        if (this->children[2]) {
            this->children[2]->flatten(); // ArgList - can be absent
        }

        if (this->children[3]) {
            this->children[3]->flatten(); // OperatorBlock
        }
        else {
            LOG(getClassName() + "->children[3] is null");
        }
    }
};

class Identifier: public Expression {
public:
    Identifier () {

    }

    Identifier (NodeValue * nodeValue) : Expression(nodeValue) {

    }

    std::string getClassName() {
        return "Identifier";
    }

    Commands getCommand () {
        return C_NOOP;
    }

    void flatten() {
    }
};

class Literal : public Expression {
public:
    Literal() {

    }

    Literal (NodeValue * nodeValue) : Expression(nodeValue) {

    }

    std::string getClassName() {
        return "Literal";
    }

    Commands getCommand () {
        return C_NOOP;
    }

    void flatten() {
    }
};

class Increment: public Command { // [LeftPartExpr]
public:
    Increment () {

    }

    Increment (NodeValue * nodeValue) : Command(nodeValue) {

    }
    std::string getClassName() {
        return "Increment";
    }

    Commands getCommand () {
        return C_INC;
    }

    void flatten() {
        if (this->children[0]) {
            this->children[0]->flatten(); // LeftPartExpr
        }
        else {
            LOG(getClassName() + "->children[0] is null");
        }

    }
};

class OperatorBlock : public Node  { //[Command, OperatorBlock]
public:
    OperatorBlock () {

    }

    OperatorBlock (NodeValue * nodeValue) : Node(nodeValue) {

    }
    std::string getClassName() {
        return "OperatorBlock";
    }

    Commands getCommand () {
        return C_BLOCK;
    }

    void flatten() {
        if (this->children[0]) {
            this->children[0]->flatten(); // flatten operator
        }
        else {
            LOG(getClassName() + "->children[0] is null");
        }
        OperatorBlock * iter = (OperatorBlock *) this->children[1];
        OperatorBlock * tmp;
        this->children.pop_back();
        while (iter) {
            tmp = iter;
            if (iter->children[0]) {
                iter->children[0]->flatten(); // Command
                this->children.push_back(iter->children[0]);
            }
            else {
                LOG(iter->getClassName() + "->children[0] is null");
            }
            iter = (OperatorBlock *) iter->children[1];
            tmp->children.clear();
            delete tmp;
        }
    }
};



class Return: public Command { // [Expression]
public:
    Return () {

    }

    Return (NodeValue * nodeValue) : Command(nodeValue) {

    }

    std::string getClassName() {
        return "Return";
    }

    Commands getCommand () {
        return C_RETURN;
    }

    void flatten() {
        if (this->children[0]) {
            this->children[0]->flatten(); //Expression
        }
        else {
            LOG(getClassName() + "->children[0] is null");
        }
    }

};

class UnaryExpr: public Expression {
public:
    UnaryExpr () {

    }

    UnaryExpr (NodeValue * nodeValue) : Expression(nodeValue) {

    }
    std::string getClassName() {
        return "UnaryExpr";
    }

    Commands getCommand () {
        return C_NOOP;
    }

    void flatten() {
        if (this->children[0]) {
            this->children[0]->flatten(); //can be expression or Condition
        }
        else {
            LOG(getClassName() + "->children[0] is null");
        }
    }
};


class VariableDecl: public Declaration { // [type, name dimensions, init]
public:
    VariableDecl () {

    }

    VariableDecl (NodeValue * nodeValue) : Declaration(nodeValue) {

    }

    std::string getClassName() {
        return "VariableDecl";
    }

    Commands getCommand () {
        return C_VARDECL;
    }

    void flatten() {
        if (this->children[2]) {
            this->children[2]->flatten(); // ArrayDim object - can be absent
        }

        if (this->children[3]) {
            this->children[3]->flatten(); //rightPartExpr
        }
        else {
            LOG(getClassName() + "children[3] is null");
        }
    }
};

class WhileLoop: public Loop {
public:
    WhileLoop () {

    }

    WhileLoop (NodeValue * nodeValue) : Loop(nodeValue) {

    }

    std::string getClassName() {
        return "WhileLoop";
    }

    Commands getCommand () {
        return C_WHILE;
    }

    void flatten() {
        if (this->children[0]) {
            this->children[0]->flatten(); // Condition
        }
        else {
            LOG(getClassName() + "->children[0] is null");
        }
        if (this->children[1]) {
            this->children[1]->flatten(); // OperatorBlock
        }
        else {
            LOG(getClassName() + "->children[1] is null");
        }
    }
};

#endif // NODE_H
