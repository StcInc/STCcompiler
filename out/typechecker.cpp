#ifndef TYPE_H
#define TYPE_H

#include <cassert>
#include <string>
#include <vector>
#include <map>
#include "node.cpp"
#include "nodevalue.h"


/* Type descriptor */
struct TypeRec {
    Type type;

    /* Total length of memory area alocated for symbol
        == 0, if variable is not an array
    */
    int arrayLen;

    /* Vector of dimensions for multi dimensional arrays
        - empty, if variable is not an array
    */
    std::vector<int> dimens;

    TypeRec(Type t) : type(t) {}
};


/* Variable descriptor */
struct VarDescriptor {
    /* Number of corresponding element in type descriptor table */
    int typeRecNum;

    /* True, if there was an assignment to the variable up to the current moment
        - can be usefull to find unused variables
        - always true for function parameters
    */
    bool isAssigned;

    VarDescriptor(int typeNum) : typeRecNum(typeNum) {

    }

};

/* Function descriptor */
struct FunDescriptor {
    /* Number of corresponding element in type descriptor table */
    int typeRecNum;

    /* Funciton's local variables */
    std::map<std::string, VarDescriptor * > env;

    /* Function parameters */
    std::map<std::string, VarDescriptor * > params;

    FunDescriptor(int typeNum) : typeRecNum(typeNum) {

    }

    ~FunDescriptor() {
        for (std::map<std::string, VarDescriptor *>::iterator it = env.begin(); it != env.end(); ++it) {
            delete it->second;
        }

        for (std::map<std::string, VarDescriptor *>::iterator it = params.begin(); it != params.end(); ++it) {
            delete it->second;
        }
    }
};



class TypeChecker {
public:
    /* Symbol table */
    std::map<std::string, FunDescriptor * > funs;

    /* Type table */
    std::vector<TypeRec *> types;


    TypeChecker() {
        initTypes();
    }

    void initTypes() {
        types.push_back(new TypeRec(T_VOID));
        types.push_back(new TypeRec(T_INT));
        types.push_back(new TypeRec(T_CHAR));
        types.push_back(new TypeRec(T_FLOAT));
        types.push_back(new TypeRec(T_BOOL));
        types.push_back(new TypeRec(T_STRING));
    }

    ~TypeChecker () {
        for (std::map<std::string, FunDescriptor *>::iterator it = funs.begin(); it != funs.end(); ++it) {
            delete it->second;
        }

        for (int i = 0; i < types.size(); ++i) {
            delete types[i];
        }
    }

    int getTypeRecNum(Type type) {
        for (int i = 0; i < types.size(); ++i) {
            if (types[i]->type == type) {
                return i;
            }
        }
        return -1;
    }

    /*
        Checks the type of the given expression,
        adds a new record into types table, if type is not present there yet
        returns the number of record in types table, or -1 if check fails
     */
    int getTypeNumOfExpr(Expression * expr, FunDescriptor * descriptor) {

        return -1; // fail
    }

    /*
        Type checking launcher - main method to be called
        checks all the declarations of the program for types
     */
    bool typeCheck(Program * program) {
        bool res = true;
        for (int i = 0; i < program->children.size(); ++i) {
            res = res && typeCheckFun((FunctionDecl *)program->children[i]);
        }
        return res;
    }

    bool typeCheckFun(FunctionDecl * fun) { // fun : [type, name, args, body]
        std::string * name = ((StringValue *)fun->children[1]->value)->value;

        // check wheter the name already exists in this->funs or not
        if (funs.find(*name) == funs.end()) { // symbol is not tied, add to the table
            TypeNode * typeNode = (TypeNode*) fun->children[0];
            int typeNum = getTypeRecNum(typeNode->type);
            assert(typeNum >= 0);

            FunDescriptor * descriptor = new FunDescriptor(typeNum);

            bool res = true;

            //work with parameters
            res = res && typeCheckParams((ArgList*)fun->children[2], descriptor, name);

            // check body
            res = res && typeCheckBody((OperatorBlock *)fun->children[3], descriptor, name);

            // add sym to this->funs
            funs.insert(std::pair<std::string, FunDescriptor * >(*name, descriptor));

            return res;
        }
        else {
            std::cout << "Symbol already used:" << *name << std::endl;
            return false;
        }
    }


    bool typeCheckParams(ArgList * args, FunDescriptor * descriptor, std::string * funName) {
        for (int i = 0; i < args->children.size(); ++i) {
            Arg * arg = (Arg*) args->children[i]; // [type, name]

            assert(arg->children.size() == 2);
            assert(arg->children[0] != NULL);
            assert(arg->children[1] != NULL);

            std::string * name = ((StringValue *)arg->children[1]->value)->value;

            // check name in descriptor->params
            if (descriptor->params.find(*name) == descriptor->params.end()) {
                TypeNode * typeNode = (TypeNode *) arg->children[0];
                int typeNum = getTypeRecNum(typeNode->type);

                assert(typeNum >= 0);

                VarDescriptor * p = new VarDescriptor(typeNum);
                p->isAssigned = true;
                descriptor->params.insert(std::pair<std::string, VarDescriptor *>(*name, p));
            } else {
                std::cout << "Symbol "
                          << *name
                          << " already used as parameter of function "
                          << *funName
                          << std::endl;
                return false;
            }
        }
        return true;
    }

    bool typeCheckBody(OperatorBlock * body, FunDescriptor * descriptor, std::string * funName) {
        bool res = true;
        for (int i = 0; i < body->children.size(); ++i) {
            Node * comand = body->children[i];
            switch (comand->getCommand()) {
                case C_NOOP :
                    // just pass it
                    break;
                case C_ASG :
                    res = res && typeCheckAssignment((Assignment *)comand, descriptor);
                    break;
                case C_VARDECL:
                    res = res && typeCheckVarDecl((VariableDecl*)comand, descriptor);
                    break;
                case C_IF :
                    res = res && typeCheckIf((Conditional*)comand, descriptor);
                    break;
                case C_FOR :
                    res = res && typeCheckFor((ForLoop *)comand, descriptor);
                    break;
                case C_WHILE :
                    res = res && typeCheckWhile((WhileLoop *)comand, descriptor);
                    break;
                case C_POST :
                    res = res && typeCheckPost((PostLoop *)comand, descriptor);
                    break;
                case C_FCALL : {
                    FunctionCall * call = (FunctionCall*)comand;
                    std::string * calledName = ((StringValue*)call->children[0]->value)->value;
                    if (funs.find(*calledName) == funs.end()) { // called unknown Funciton
                        std::cout << "called unknown function: " << *calledName << std::endl;
                    }
                    else {
                        FunDescriptor * calledFun = funs[*calledName];
                        res = res && typeCheckParamsForFun(descriptor, calledFun, (ParamList*)call->children[1]);
                    }
                    break;
                }
                case C_RETURN : {
                    if (comand->children.size() > 0) {
                        int typeNum = getTypeNumOfExpr((Expression *)comand->children[0], descriptor);
                        assert(typeNum >= 0);
                        if (typeNum != descriptor->typeRecNum) {
                            res = false;
                            std::cout << "Return expression type must match the function type"
                                      << *funName
                                      << std::endl;
                        } // else res depend on it's own
                    }
                    else { // return; - function's type had to be void
                        if (descriptor->typeRecNum != getTypeRecNum(T_VOID)) {
                            res = false;
                            std::cout << "Function return type must be void to use return without expression "
                                      << *funName
                                      << std::endl;
                        } // else res depend on it's own
                    }
                    break;
                }
                case C_BREAK :
                    // just pass
                    break;
                case C_CONTINUE :
                    // just pass
                    break;
                case C_INC : {
                    LeftPartExpr * ex = (LeftPartExpr*)comand->children[0];
                    // if expr has no-incrementable type
                    // res = false;
                    break;
                }
                case C_BLOCK :
                    res = res && typeCheckBody((OperatorBlock *)comand, descriptor, funName);
                    break;
                default :
                    std::cout << "Unexpected node type "
                              << comand->getClassName()
                              << std::endl;
                    break;
            }
        }
        return true;
    }

    bool typeCheckParamsForFun(FunDescriptor * context, FunDescriptor * descriptor, ParamList * params) {
        return true;
    }

    bool typeCheckBlock(OperatorBlock * block, FunDescriptor * descriptor) {
        return true;
    }

    bool typeCheckAssignment(Assignment * asg, FunDescriptor * descriptor) {
        // take the type of left part - LeftPartExpr
        LeftPartExpr * leftPart = (LeftPartExpr*)asg->children[0];
        // leftPart->

        int leftTypeNum = -1;

        // find the type of expr at right - rightPartExpr
        Node * rightPart = asg->children[1];
        // could be Expression : BinaryExpr, UnaryExpr, FunctionCall, Identifier, Literal
        // could be LeftPartExpr
        // could be ArrayItems
        // could be Increment

        //TODO: implement

        int rightTypeNum = -1;

        assert(leftTypeNum >= 0);
        assert(rightTypeNum >= 0);

        // compare them
        if (leftTypeNum == rightTypeNum) {
            return true;
        }
        return false;
    }

    bool typeCheckVarDecl(VariableDecl * vDecl, FunDescriptor * descriptor) {
        // check all the array dimensions
        return true;
    }

    bool typeCheckIf(Conditional * cond, FunDescriptor * descriptor) {
        return true;
    }

    bool typeCheckFor(ForLoop * loop, FunDescriptor * descriptor) {
        return true;
    }

    bool typeCheckWhile(WhileLoop * loop, FunDescriptor * descriptor) {
        return true;
    }

    bool typeCheckPost(PostLoop * loop, FunDescriptor * descriptor) {
        return true;
    }

    bool typeCheckFunCall(FunctionCall * call, FunDescriptor * descriptor) {
        return true;
    }

    bool typeCheckInc(Increment * incr, FunDescriptor * descriptor) {
        return true;
    }

    // TODO: add handlers for different commands


};


#endif // TYPE_H

int main() {

}
