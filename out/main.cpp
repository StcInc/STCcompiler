#include <iostream>
#include "node.cpp"
extern Program* program;
extern int yyparse();

int main() {
    yyparse();
    if (program) {
        program->flatten();
        program->print();
        delete program;
    }

    return 0;
}
