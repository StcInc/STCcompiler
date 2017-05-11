#include <iostream>
#include "node.cpp"
// #include "typechecker.cpp"

extern Program* program;
extern int yyparse();

int main() {
    yyparse();
    if (program) {
        program->flatten();
        program->print();

        // TypeChecker typeChecker();
        // if (typeChecker.typeCheck(program)) {
        //     std::cout << "Type ckeck passed" << std::endl;
        // }
        // else {
        //     std::cout << "Type ckeck failed" << std::endl;
        // }

        // TODO: add other semantics checks like break, continue inside loops, etc.

        delete program;
    }

    return 0;
}
