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

    TypeRec(Type t) : type(t), arrayLen(0) { }
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

    bool bodyDefined;

    /* Funciton's local variables */
    std::map<std::string, VarDescriptor * > env;

    /* Function parameters */
    std::map<std::string, VarDescriptor * > params;
    std::vector<int> paramTypeNums; /* keeps type nums of the parameters */

    FunDescriptor(int typeNum) : typeRecNum(typeNum), bodyDefined(false) {

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


    /**
     * Finds a number of given simple type in type table
     *   returns number of type descriptor in types table
     *   or -1, if not found
     */
    int getTypeRecNum(Type type) {
        for (int i = 0; i < types.size(); ++i) {
            if (types[i]->type == type && types[i]->arrayLen == 0) {
                return i;
            }
        }
        return -1;
    }

    /**
     * Finds a number of given type with dimensions for an array
     * returns number of type descriptor in types table (typeRecNum)
     * or -1, if not found
     */
    int findArrayTypeId(Type type, int arrayLength, std::vector<int> dimensions) {
        TypeRec * t;
        for (int i = 0; i < types.size(); ++i) {
            t = types[i];
            if (t->type == type && t->arrayLen == arrayLength && t->dimens.size() == dimensions.size()) {
                bool same = true;
                for (int j = 0; j < t->dimens.size(); ++j) {
                    if (t->dimens[j] != dimensions[j]) {
                        same = false;
                    }
                }
                if (same) {
                    return i;
                }
             }
        }
        return -1;
    }

    /* Checks operand types of binary expression
        and returns typeRecNum of resulting expression
    */
    int getBinaryOpType(BinOp * binOp, int typeL, int typeR) {
        if (typeL != typeR) {
            return -1;
        }
        switch (binOp->getOpType()) {
            case TARITH_OP: if (types[typeL]->type == T_INT || types[typeL]->type == T_FLOAT) {
                // args are INT (or FLOAT) and retval type INT (or FLOAT)
                return typeL;
            }
            case TBOOL_OP: if (types[typeL]->type == T_BOOL) {
                // args are BOOL and retval type is BOOL
                return typeL;
            }
            case TCOMP_OP: if (types[typeL]->type == T_INT || types[typeL]->type == T_FLOAT) {
                // args are of same type AND retval type is boolean
                return getTypeRecNum(T_BOOL);
            }
            default: return -1;
        }
    }

    /* Checks operand type of unary Expression and mathes it with the operator
        returns typeRecNum of resulting expression
    */
    int getUnaryOpType(UnOp * unOp, int typeC) {
        if ((unOp->getOpType() == TARITH_OP)
            && (types[typeC]->type == T_INT || types[typeC]->type == T_FLOAT))
        {
            return typeC;
        }
        else if ((unOp->getOpType() == TBOOL_OP) && (types[typeC]->type == T_BOOL)) {
            return typeC;
        }
        else {
            return -1;
        }

    }

    /* Checks the type of the given expression,
        adds a new record into types table, if type is not present there yet
        returns the number of record in types table, or -1 if check fails
     */
    int getTypeNumOfExpr(Expression * expr, FunDescriptor * descriptor) {
        std::cout << "Checking expression: " << expr->getClassName() << '\n';
        if (expr->getClassName() == "BinaryExpr") {
            assert(expr->children.size() == 2);

            assert(expr->children[0]);
            int typeL = getTypeNumOfExpr((Expression*) expr->children[0], descriptor);
            assert(typeL >= 0);

            assert(expr->children[1]);
            int typeR = getTypeNumOfExpr((Expression*) expr->children[1], descriptor);
            assert(typeR >= 0);

            return getBinaryOpType((BinOp *)expr->value, typeL, typeR);
        }
        else if (expr->getClassName() == "UnaryExpr") {
            assert(expr->children.size() == 1);
            assert(expr->children[0]);
            int typeC = getTypeNumOfExpr((Expression*) expr->children[0], descriptor);
            return getUnaryOpType((UnOp *)expr->value, typeC);
        }
        else if (expr->getClassName() == "Literal") {
            if (expr->value->getClassName() == "IntValue") {
                return getTypeRecNum(T_INT);
            }
            else if (expr->value->getClassName() == "CharValue") {
                return getTypeRecNum(T_CHAR);
            }
            else if (expr->value->getClassName() == "StringValue") {
                return getTypeRecNum(T_STRING);
            }
            else if (expr->value->getClassName() == "FloatValue") {
                return getTypeRecNum(T_FLOAT);
            }
            else if (expr->value->getClassName() == "BoolValue") {
                return getTypeRecNum(T_BOOL);
            }
        }
        else if (expr->getClassName() == "FunctionCall") {
            return getFunCallTypeNum(expr, descriptor);
        }
        else if (expr->getClassName() == "LeftPartExpr") {
            return getLeftPartExprTypeNum((LeftPartExpr*)expr, descriptor);
        }
        else if (expr->getClassName() == "Increment") {
            assert(expr->children.size() == 1);
            int typeNum = getLeftPartExprTypeNum((LeftPartExpr*) expr->children[0], descriptor);
            return typeNum;
        }
        else if (expr->getClassName() == "ArrayItems") {
            // check each and every element and the depth of the array, and dimensions
            //TODO: implement
            // WARN: flattening of array items may work wrong! or may not)))

            return -1;
        }

        std::cout << "Fail to match expression type ";
        expr->print();
        std::cout << std::endl;
        return -1; // fail to match expression type
    }


    int getFunCallTypeNum(Expression * expr, FunDescriptor * descriptor) {
        Identifier * fIdentifier = (Identifier *) expr->children[0];
        StringValue * nameValue = (StringValue *)fIdentifier->value;
        std::string * funName = nameValue->value;
        std::map<std::string, FunDescriptor *>::iterator it;

        it = funs.find(*funName);
        if (it != funs.end()) {
            FunDescriptor * desc = it->second;
            if (desc->params.size() > 0) { // params expected for function call
                if (expr->children.size() > 1) { // params given, and expected
                    ParamList* params = (ParamList*) expr->children[1];
                    if (typeCheckParamsForFunCall(descriptor, desc, params)) { // if parameters correct
                        return desc->typeRecNum;
                    }
                    else { // parameters are incorrect
                        std::cout << "Params for fun call are incorrect "
                                  << *funName
                                  << std::endl;
                        return -1;
                    }
                }
                else { // no params given, but expected
                    std::cout << "No parameters given to function "
                              << *funName
                              << std::endl;
                    return -1;
                }
            }
            else { // no parameters expected for function call
                if (expr->children.size() > 0) { // Unexpected parameters given
                    std::cout << "Unexpected parameters given to function "
                              << *funName
                              << std::endl;
                    return -1;
                }
                else { // no parameters given, no parameters expected
                    return desc->typeRecNum;
                }
            }
        }
        else { // function descriptor not found
            std::cout << "Undefined function called: " << *funName;
            return -1;
        }
    }

    int getLeftPartExprTypeNum(LeftPartExpr * incExp, FunDescriptor * descriptor) {
        assert(incExp->children.size() > 0);
        Identifier * id = (Identifier *)incExp->children[0];
        StringValue* nameValue = (StringValue*)id->value;
        std::string * name = nameValue->value;

        // check if symbol defined in env or params
        std::map<std::string, VarDescriptor*>::iterator it;
        it = descriptor->env.find(*name);
        if (it == descriptor->env.end()) {
            it = descriptor->params.find(*name);
            if (it == descriptor->params.end()) {
                std::cout << "Variable " << *name << " was not defined " << std::endl;
                incExp->print();
                return -1;
            }
        }

        VarDescriptor * variable = (VarDescriptor*)it->second;

        for (int i = 1; i < incExp->children.size(); ++i) { // for each Indexing
            Expression * dimen = (Expression*)incExp->children[i];
            if (dimen) {
                int dimenType = getTypeNumOfExpr(dimen, descriptor);
                assert(dimenType >= 0);
                if (dimenType != getTypeRecNum(T_INT)) {
                    std::cout << "Array dimensions must be integer values ";
                    incExp->print();
                    return -1;
                }
            }
        }
        return variable->typeRecNum;
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
        assert(fun->children.size() >= 2);
        assert(fun->children[0]);
        assert(fun->children[1]);

        std::string * name = ((StringValue *)fun->children[1]->value)->value;
        std::cout << "Type checking fun " << *name << std::endl;

        std::map<std::string, FunDescriptor *>::iterator it = funs.find(*name);

        if (it == funs.end()) { // symbol is not tied, add to the table
            TypeNode * typeNode = (TypeNode*) fun->children[0];
            int typeNum = getTypeRecNum(typeNode->type);
            assert(typeNum >= 0);

            FunDescriptor * descriptor = new FunDescriptor(typeNum);

            bool res = true;

            //work with parameters
            if (fun->children.size() >= 3 && fun->children[2]) {
                res = res && typeCheckFunctionArgs((ArgList*)fun->children[2], descriptor, name);
            }

            // check body
            if (fun->children.size() == 4 && fun->children[3]) {
                res = res && typeCheckBody((OperatorBlock *)fun->children[3], descriptor, name);
            }

            // add sym to this->funs
            funs.insert(std::pair<std::string, FunDescriptor * >(*name, descriptor));

            return res;
        }
        else if (!it->second->bodyDefined) {
            // check the parameters to match the predefinition
            FunDescriptor * descriptor = it->second;
            TypeNode * typeNode = (TypeNode *) fun->children[0];
            if (getTypeRecNum(typeNode->type) == descriptor->typeRecNum) {
                // check parameters

                // TODO: how to check argument order in descriptor

                return true;
            }
            else { // predefined type doesn't match
                return false;
            }
        }
        else {
            std::cout << "Symbol already used:" << *name << std::endl;
            return false;
        }
    }

    /* Returns true if arguments in function declaration are defined correctly
    */
    bool typeCheckFunctionArgs(ArgList * args, FunDescriptor * descriptor, std::string * funName) {
        std::cout << "checking fun args " << *funName << std::endl;

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
                descriptor->paramTypeNums.push_back(typeNum);

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

    /* Returns true if all the operators in function body have type correctness
    */
    bool typeCheckBody(OperatorBlock * body, FunDescriptor * descriptor, std::string * funName) {
        std::cout << "checking fun body " << *funName << std::endl;
        bool res = true;

        for (int i = 0; i < body->children.size(); ++i) {
            Node * command = body->children[i];
            switch (command->getCommand()) {
                case C_NOOP :
                    // just pass it
                    break;
                case C_ASG :
                    res = res && typeCheckAssignment((Assignment *)command, descriptor);
                    break;
                case C_VARDECL:
                    res = res && typeCheckVarDecl((VariableDecl*)command, descriptor, funName);
                    break;
                case C_IF :
                    res = res && typeCheckIf((Conditional*)command, descriptor, funName);
                    break;
                case C_FOR :
                    res = res && typeCheckFor((ForLoop *)command, descriptor, funName);
                    break;
                case C_WHILE :
                    res = res && typeCheckWhile((WhileLoop *)command, descriptor, funName);
                    break;
                case C_POST :
                    res = res && typeCheckPost((PostLoop *)command, descriptor, funName);
                    break;
                case C_FCALL : {
                    FunctionCall * call = (FunctionCall*)command;
                    assert(call->children.size() > 0);
                    assert(call->children[0]);

                    Identifier * calledId = (Identifier *) call->children[0];
                    StringValue * nameValue = (StringValue*) calledId->value;
                    std::string * calledName = nameValue->value;

                    int typeNum = getFunCallTypeNum(call, descriptor);
                    if (typeNum >= 0) {
                        res = false;
                        std::cout << "Function call is incorrect"
                                  << *calledName
                                  << " in "
                                  << funName
                                  << std::endl;

                    }
                    break;
                }
                case C_RETURN : {
                    if (command->children.size() > 0) {
                        int typeNum = getTypeNumOfExpr((Expression *)command->children[0], descriptor);
                        assert(typeNum >= 0);
                        if (typeNum != descriptor->typeRecNum) {
                            res = false;
                            std::cout << "Return expression type must match the function type "
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
                    Expression * expr = (Expression *) command->children[0];
                    int exprType = getTypeNumOfExpr(expr, descriptor);
                    if (exprType != getTypeRecNum(T_INT)) {
                        res = false;
                        std::cout << "Incrementable value had to have type of int "
                                  << *funName
                                  << std::endl;
                    } // else res depend on it's own
                    break;
                }
                case C_BLOCK : {
                    OperatorBlock * block = (OperatorBlock *) command;
                    res = res && typeCheckBody(block, descriptor, funName);
                    break;
                }
                default :
                    std::cout << "Unexpected node type "
                              << command->getClassName()
                              << std::endl;
                    break;
            }
        }
        return res;
    }

    bool typeCheckParamsForFunCall(FunDescriptor * context, FunDescriptor * descriptor, ParamList * params) {
        if (params->children.size() != descriptor->params.size()) {
            std::cout << "Count of parameters given to function doesn't match count of params in declaration" << std::endl;
            return false;
        }
        for (int i = 0; i < params->children.size(); ++i) {
            Expression * param = (Expression *) params->children[i];
            int typeNum = getTypeNumOfExpr(param, context);

            if (typeNum < 0) {
                std::cout << "Incorrect param type of " << i << std::endl;
                return false;
            }
            if (typeNum != descriptor->paramTypeNums[i]) {
                std::cout << "Type of parameter given to fun doesn't match wtih declaration" << std::endl;
                return false;
            }
        }
        return true;
    }

    bool typeCheckAssignment(Assignment * asg, FunDescriptor * descriptor) {
        std::cout << "checking assignment" << std::endl;
        assert(asg->children.size() == 2);

        assert(asg->children[0]);
        LeftPartExpr * leftPart = (LeftPartExpr*) asg->children[0];
        int leftTypeNum = getLeftPartExprTypeNum(leftPart, descriptor);
        assert(leftTypeNum >= 0);

        assert(asg->children[1]);
        Expression * rightPart = (Expression*) asg->children[1];
        int rightTypeNum = getTypeNumOfExpr(rightPart, descriptor);
        assert(rightTypeNum >= 0);

        if (leftTypeNum == rightTypeNum) {
            return true;
        }
        return false;
    }

    bool typeCheckVarDecl(VariableDecl * varDecl, FunDescriptor * descriptor, std::string * funName) {
        std::cout << "checking var declaration" << std::endl;
        assert(varDecl->children.size() >= 2);

        assert(varDecl->children[0]);
        TypeNode * typeNode = (TypeNode *) varDecl->children[0];
        int typeRecNum = getTypeRecNum(typeNode->type);
        assert(typeRecNum >= 0);

        assert(varDecl->children[1]);
        Identifier * id = (Identifier*) varDecl->children[1];
        std::string * name = ((StringValue*)id->value)->value;

        std::map<std::string, VarDescriptor*> :: iterator it;
        it = descriptor->params.find(*name);
        if (it == descriptor->params.end()) {
            it = descriptor->env.find(*name);
            if (it != descriptor->env.end()) {
                std::cout << "Variable already defined " << *name << std::endl;
                return false;
            }
        }
        else {
            std::cout << "Attempting to override function parameter " << *name << std::endl;
            return false;
        }

        // create new variable
        VarDescriptor * varDesc = new VarDescriptor(typeRecNum);

        if (varDecl->children.size() >= 3 && varDecl->children[2]) {

            // check all the array dimensions if present
            ArrayDim * dimensions = (ArrayDim *)varDecl->children[2];
            int dimenType = -1;

            for (int i = 1; i < dimensions->children.size(); ++i) { // for each Indexing
                Expression * dimen = (Expression*)dimensions->children[i];
                if (dimen) {
                    dimenType = getTypeNumOfExpr(dimen, descriptor);
                    assert(dimenType >= 0);

                    if (dimenType != getTypeRecNum(T_INT)) {
                        std::cout << "Array dimensions must be integer values ";
                        varDecl->print();
                        std::cout << std::endl;
                        return -1;
                    }
                }
            }

        }

        if (varDecl->children.size() == 4 && varDecl->children[3]) {

            // check initialization
            Expression * initExpr = (Expression*)varDecl->children[3];
            int typeR = getTypeNumOfExpr(initExpr, descriptor);
            if (typeR < 0) {
                std::cout << "Right part of expressions has incorrect type" << std::endl;
                return false;
            }

            if (typeR != typeRecNum) {
                std::cout << "Ivalid right part of assignment at variable declaration ";
                varDecl->print();
                std::cout << std::endl;
                delete varDesc;
                return false;
            }
            varDesc->isAssigned = true;
        }
        // add varDesc to descriptor->env
        descriptor->env.insert(std::pair<std::string, VarDescriptor *>(*name, varDesc));

        return true;
    }

    bool typeCheckIf(Conditional * conditional, FunDescriptor * descriptor, std::string * funName) {
        std::cout << "checking if " << std::endl;
        assert(conditional->children.size() >= 2);
        assert(conditional->children[0]);

        Expression * condition = (Expression *) conditional->children[0];
        int typeCond = getTypeNumOfExpr(condition, descriptor);
        if (typeCond != getTypeRecNum(T_BOOL)) {
            std::cout << "Condition in IF statement must have boolean type " << std::endl;
            return false;
        }

        assert(conditional->children[1]);
        OperatorBlock * thenBranch = (OperatorBlock *) conditional->children[1];


        if (!typeCheckBody(thenBranch, descriptor, funName)) {
            std::cout << "Then branch in if is type incorrect" << std::endl;
            return false;
        }

        if (conditional->children.size() == 3 && conditional->children[2]) {
            if (conditional->children[2]->getClassName() == "Conditional") {
                return typeCheckIf((Conditional *) conditional->children[2], descriptor, funName);
            }
            else if (conditional->children[2]->getClassName() == "OperatorBlock") {
                return typeCheckBody((OperatorBlock *) conditional->children[2], descriptor, funName);
            }
            else {
                std::cout << "Could not match the node type of else branch" << std::endl;
                return false;
            }
        }

        return true;
    }

    bool typeCheckFor(ForLoop * loop, FunDescriptor * descriptor, std::string * funName) {
        std::cout << "checking for loop" << std::endl;
        assert(loop->children.size() > 0);
        assert(loop->children[0]);
        ForInit * init = (ForInit *) loop->children[0];

        assert(init->children.size() == 3);
        assert(init->children[0]);
        assert(init->children[1]);
        assert(init->children[2]);

        // loop counter
        VariableDecl * varDecl = (VariableDecl *) init->children[0];
        if (typeCheckVarDecl(varDecl, descriptor, funName)) {
            std::cout << "Variable declarations is type incorrect in "
                      << *funName
                      << std::endl;
        }

        // loop condition
        if (getTypeNumOfExpr((Expression *) init->children[1], descriptor) != getTypeRecNum(T_BOOL)) {
            std::cout << "Condition in FOR statement must have boolean type in "
                      << *funName
                      << std::endl;
            return false;
        }
        // each operation
        if (getTypeNumOfExpr((Expression *) init->children[2], descriptor) < 0) {
            std::cout << "Loop operation in FOR statement has incorrect type in "
                      << *funName
                      << std::endl;
            return false;
        }

        if (loop->children.size() == 2 && loop->children[1]) { // body can be absent
            OperatorBlock * body = (OperatorBlock *) loop->children[1];
            if (!typeCheckBody(body, descriptor, funName)) {
                std::cout << "For loop body has incorrect types in it" << std::endl;
                return false;
            }
        }
        // delete loop variable form for descriptor->env
        StringValue * nameValue = (StringValue *)varDecl->children[1]->value;
        std::string * name = nameValue->value;
        VarDescriptor * varDesc = descriptor->env[*name];
        if (varDesc) {
            delete varDesc;
        }
        descriptor->env.erase(*name);
        return true;
    }

    bool typeCheckWhile(WhileLoop * loop, FunDescriptor * descriptor, std::string * funName) {
        std::cout << "checking while loop" << std::endl;
        assert(loop->children.size() > 0);
        assert(loop->children[0]);
        Expression * condition = (Expression * ) loop->children[0];
        if (getTypeNumOfExpr(condition, descriptor) != getTypeRecNum(T_BOOL)) {
            std::cout << "Condition in WHILE statement must have boolean type in "
                      << *funName
                      << std::endl;
            return false;
        }

        if (loop->children.size() == 2 && loop->children[1]) {
            OperatorBlock * body = (OperatorBlock*) loop->children[1];
            return typeCheckBody(body, descriptor, funName);
        }
        return true;
    }

    bool typeCheckPost(PostLoop * loop, FunDescriptor * descriptor, std::string * funName) {
        std::cout << "checking post cond loop" << std::endl;
        assert(loop->children.size() == 2);
        assert(loop->children[0]);
        assert(loop->children[1]);

        OperatorBlock * body = (OperatorBlock *) loop->children[0];
        bool res = typeCheckBody(body, descriptor, funName);
        if (!res) {
            std::cout << "Do while loop body is type incorrect in "
                      << *funName
                      << std::endl;
        }

        Expression * condition = (Expression * ) loop->children[1];
        if (getTypeNumOfExpr(condition, descriptor) != getTypeRecNum(T_BOOL)) {
            std::cout << "Condition in WHILE statement must have boolean type in "
                      << *funName
                      << std::endl;
            return false;
        }

        return true;
    }

    // TODO: add handlers for different commands


};


#endif // TYPE_H

// int main() {
//
// }
