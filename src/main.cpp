#include <iostream>
#include "node.cpp"
#include "typechecker.cpp"

extern Program* program;
extern int yyparse();

int main() {
    yyparse();
    if (program) {
        program->flatten();
        program->print();

        TypeChecker typeChecker;
        if (typeChecker.typeCheck(program)) {
            std::cout << "Type check passed" << std::endl;
        }
        else {
            std::cout << "Type check failed" << std::endl;
        }

        // TODO: add other semantics checks like break, continue inside loops, etc.

        delete program;
    }

    return 0;
}
