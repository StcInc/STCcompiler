#ifndef CODEGEN
#define CODEGEN

#include <string>
#include <iostream>
#include <vector>
#include "node.cpp"
#include "nodevalue.h"
#include "typechecker.cpp"

#include <typeinfo>
#include <llvm/IR/Module.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/CallingConv.h>
#include <llvm/IR/IRPrintingPasses.h>
#include <llvm/IR/IRBuilder.h>

#include <llvm/Support/TargetSelect.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/MCJIT.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/Support/raw_ostream.h>

using namespace llvm;

class CodeGenerator {
private:
    TypeChecker & typeChecker;
    LLVMContext context;
    Module * module = nullptr;
    Function * mainFunction = nullptr;

public:
    CodeGenerator(TypeChecker & checker) : typeChecker(checker) {
        module = new Module("main", context);
    }

    void generate(Program * program) {
        std::cout << "Generating code...\n";

        /* Create the top level interpreter function to call as entry */
        ArrayRef<llvm::Type*> argTypes;
        FunctionType *ftype = FunctionType::get(llvm::Type::getVoidTy(context), argTypes, false);
        mainFunction = Function::Create(ftype, GlobalValue::InternalLinkage, "main", module);
        BasicBlock *bblock = BasicBlock::Create(context, "entry", mainFunction, 0);

        /* Push a new variable/block context */
        pushBlock(bblock);
        //    root.codeGen(*this); /* emit bytecode for the toplevel block */
        // TODO: implement

        ReturnInst::Create(context, bblock);
        popBlock();

        std::cout << "Code is generated.\n";
        std::cout << "=========CODE=========\n";
        llvm::legacy::PassManager pm;
        pm.add(createPrintModulePass(outs()));
        pm.run(*module);

    }

    void pushBlock(BasicBlock *block) {
        // TODO: implement
    }
    void popBlock() {
        //TODO: implement
    }
};

#endif // CODEGEN
