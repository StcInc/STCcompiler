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

        std::cout << "AST build:" << std::endl;
        program->print();

        TypeChecker typeChecker;
        if (typeChecker.typeCheck(program)) {
            std::cout << "Type check passed" << std::endl;

            std::cout << "Generating code...\n";
            CodeGenerator codeGenerator;
            codeGenerator.generate(program);

            std::cout << "Code is generated.\n";
            std::cout << "=========CODE=========\n";
            codeGenerator.printCode();
        }
        else {
            std::cout << "Type check failed" << std::endl;
        }
        delete program;
    }

    return 0;
}
