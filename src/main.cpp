#include <iostream>
#include "node.cpp"
#include "typechecker.cpp"
#include "codegen.cpp"

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

            // TODO: add other semantics checks like break, continue inside loops, etc.

            CodeGenerator codeGenerator(typeChecker);
            codeGenerator.generate(program);
        }
        else {
            std::cout << "Type check failed" << std::endl;
        }
        delete program;
    }

    return 0;
}
