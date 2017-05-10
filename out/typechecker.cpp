#ifndef TYPE_H
#define TYPE_H

#include <string>
#include <vector>
#include <map>
#include "node.cpp"
#include "nodevalue.h"

/* Type descriptor */
struct TypeRec {
    Type type;

};

/* Function descriptor */
struct FunDescriptor {
    /* Number of corresponding element in type descriptor table */
    int typeRecNum;

    /* Funciton's local variables */
    std::map<std::string, VarDescriptor * > env;

    /* Function parameters */
    std::map<std::string, VarDescriptor * > params;
};

/* Variable descriptor */
struct VarDescriptor {

    bool isParameter;

    /* Total length of memory area alocated for symbol
        == 0, if variable is not an array
    */
    int arrayLen;

    /* Vector of dimensions for multi dimensional arrays
        - empty, if variable is not an array
    */
    std::vector<int> dimens;

    /* True, if there was an assignment to the variable up to the current moment
        - can be usefull to find unused variables
        - always true for function parameters
    */
    bool isAssigned;
};


class TypeChecker {
public:
    /* Symbol table */
    std::map<std::string, FunDescriptor * > funs;

    /* Type table */
    std::vector<TypeRec *> types;

    /**
     * Returns true if first type can be extended to second type
    */
    bool is_extensible(Type type, Type toType) {
        return false;
    }

    void typeCheck(Program * program) {
        for (int i = 0; i < program->children.size(); ++i) {
            typeCheckFun((FunctionDecl *)program->children[i]);
        }
    }

    void typeCheckFun(FunctionDecl * fun) { // [type, name, args, body]
        std::string * name = ((StringValue)fun->children[1]->value);

        // check wheter the name already exists in this->funs or not
        if (funs.find(*name) == funs.end()) {
            FunDescriptor * descriptor = new FunDescriptor;

            // get number of corresponding type from type table
            descriptor->typeRecNum = 0;

            //work with parameters
            // descriptor->env;

            // add sym to this->funs
            funs.insert(std::pair<std::string, FunDescriptor * >(*name, descriptor));
        }
        else {
            std::cout << "Symbol already used:" << *name << std::endl;
        }



        // check the body
    }
};


#endif // TYPE_H
