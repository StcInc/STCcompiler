#ifndef CODEGEN
#define CODEGEN

// #define VERBOSE_CODE_GEN_INFO

#include <string>
#include <cassert>
#include <iostream>
#include <vector>
#include <deque>

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


class CodeGenBlock {
public:
    llvm::BasicBlock * block;
    std::map<std::string, llvm::Value*> env;
    std::map<std::string, int> varVersion;

    CodeGenBlock (llvm::BasicBlock * b) : block(b) {

    }

    ~CodeGenBlock() {
        delete this->block;
    }
};


class CodeGenerator {
private:
    bool entryPointFound = false;

    llvm::LLVMContext context;

    llvm::Module * module = nullptr;
    llvm::Function * mainFunction = nullptr;

    /* Keeps function's blocks order */
    std::vector<std::deque<CodeGenBlock *> *> blocks;

    /* Stores function's blocks by name */
    std::map<std::string, std::deque<CodeGenBlock *> *> funs;

public:
    CodeGenerator() {
        module = new llvm::Module("main", context);
    }

    ~CodeGenerator() {
        //TODO: free up some resources
    }

    /*
        Generates code for the given root node of the program and all subnodes
    */
    void generate(Program * program) {
        for (int i = 0; i < program->children.size(); ++i) {
            genFun((FunctionDecl *) program->children[i]);
        }
    }


    void printCode() {
        llvm::legacy::PassManager pm;
        pm.add(createPrintModulePass(outs()));
        pm.run(*module);
    }

    // GenericValue runCode() {
    //     std::cout << "Running code...n";
    //     ExistingModuleProvider *mp = new ExistingModuleProvider(module);
    //     ExecutionEngine *ee = ExecutionEngine::create(mp, false);
    //     vector<GenericValue> noargs;
    //     GenericValue v = ee->runFunction(mainFunction, noargs);
    //     std::cout << "Code was run.n";
    //     return v;
    // }


    /*
      Returns internal llvm representation of the type from AST
    */
    llvm::Type * getLLVMType(MyBasicType type) {
        switch (type) {
            case T_VOID:   return llvm::Type::getVoidTy(context);
            case T_INT:    return llvm::Type::getInt32Ty(context);
            case T_CHAR:   return llvm::Type::getInt8Ty(context);
            case T_FLOAT:  return llvm::Type::getDoubleTy(context);
            case T_BOOL:   return llvm::Type::getInt1Ty(context);
            case T_STRING: return llvm::Type::getInt8PtrTy(context); // TODO: check out the method signature, second param AS !!!!!!!
            default:       return llvm::Type::getVoidTy(context);
        }
    }


    /*
        Searches through the block stack's environments to find the value,
        associated with given variable. Returns nullptr, if value was not found
    */
    llvm::Value * getVariableValue(std::deque<CodeGenBlock *> & blockStack,
                                   std::string * varName)
    {
        std::deque<CodeGenBlock *>::iterator it;
        for (it = blockStack.begin(); it != blockStack.end(); ++it) {
            std::map<std::string, llvm::Value*> & locals = (*it)->env;
            if (locals.find(*varName) != locals.end()) {
                return locals[*varName];
            }
        }
        return nullptr;
    }

    /*
        Generates LLVM code for given function node
    */
    void genFun(FunctionDecl * decl) {
        #ifdef VERBOSE_CODE_GEN_INFO
            std::cout << "Generating code for function: ";
        #endif

        // fun type
        TypeNode * typeNode = (TypeNode *)decl->children[0];
        llvm::Type * funReturnType = getLLVMType(typeNode->type);

        // fun name
        StringValue * funNameValue = (StringValue *)decl->children[1]->value;
        std::string * funName = funNameValue->value;

        #ifdef VERBOSE_CODE_GEN_INFO
            std::cout << *funName << std::endl;
        #endif

        // fun args
        ArrayRef<llvm::Type*> argTypes;
        if (decl->children[2]) { // args -- may be absent
            ArgList * argList = (ArgList*) decl->children[2];
            for (int i = 0; i < argList->children.size(); ++i) {
                Arg * argument = (Arg*) argList->children[i];
                assert(argument);
                TypeNode * argType = (TypeNode*) argument->children[0];
                Identifier * argName = (Identifier*) argument->children[1];
                // argTypes->push(getLLVMType(argType->type));
                //TODO: add to argTypes
            }
        }

        // create function
        Function * fun;
        FunctionType *ftype = FunctionType::get(funReturnType, argTypes, false);
        fun = Function::Create(ftype, GlobalValue::InternalLinkage, *funName, module);


        if (!decl->children[3]) { // body -- may be absent
            std::cout << "Function has empty body" << std::endl;
            return;
        }

        // create body stack infrustructure
        OperatorBlock * bodyNode = (OperatorBlock*) decl->children[3];
        std::deque<CodeGenBlock*> * bodyStack = new std::deque<CodeGenBlock *>;
        funs[*funName] = bodyStack;
        blocks.push_back(bodyStack);

        // body block for function
        BasicBlock * bodyBlock;
        bodyBlock = BasicBlock::Create(context, "", fun, 0);

        CodeGenBlock * codeGenBlock = new CodeGenBlock(bodyBlock);
        bodyStack->push_front(codeGenBlock);
        genBody(*bodyStack, bodyNode, fun);
    }


    void getArgs() {
        //TODO: outfactor arglist generation from the gen function into here
    }


    void genBody(std::deque<CodeGenBlock *> & blockStack, OperatorBlock * body, Function * function) {
        #ifdef VERBOSE_CODE_GEN_INFO
            std::cout << "Generating LLVM code for operator block" << std::endl;
            body->print();
            std::cout << std::endl;
        #endif

        for (int i = 0; i < body->children.size(); ++i) {
            Node * command = body->children[i];
            switch (command->getCommand()) {
                case C_NOOP : // just pass it
                    break;
                case C_ASG :
                    genAssignment(blockStack, (Assignment *)command);
                    break;
                case C_VARDECL:
                    genVarDecl(blockStack, (VariableDecl*)command);
                    break;
                case C_IF :
                    genIf(blockStack, (Conditional*)command, function);
                    break;
                case C_FOR :
                    genFor(blockStack, (ForLoop *)command);
                    break;
                case C_WHILE :
                    genWhile(blockStack, (WhileLoop *)command);
                    break;
                case C_POST :
                    genPost(blockStack,(PostLoop *)command);
                    break;
                case C_FCALL : {
                    genFunCall(blockStack, (FunctionCall*)command);
                    break;
                }
                case C_RETURN : {
                    #ifdef VERBOSE_CODE_GEN_INFO
                        std::cout << "Generating code for return statement" << std::endl;
                    #endif

                    Return * ret = (Return*)command;
                    Value * retValue = nullptr;
                    if (ret->children[0]) { // return exression may be absent
                        retValue = getLLVMExprValue(blockStack, (Expression*)ret->children[0]);
                    } // else retValue stays null, so return type will be void

                    BasicBlock * atEnd = blockStack.front()->block;
                    ReturnInst::Create(context, retValue, atEnd);

                    //TODO: maybe that's not all with return instruction

                    break;
                }
                case C_BREAK :
                    genBreak(blockStack);
                    break;
                case C_CONTINUE :
                    genContinue(blockStack);
                    break;
                case C_INC : {
                    genInc(blockStack, (Increment *)command);
                    break;
                }
                case C_BLOCK : {
                    BasicBlock * subBlock;
                    subBlock = BasicBlock::Create(context, "", function, blockStack.front()->block);

                    CodeGenBlock * codeGenBlock = new CodeGenBlock(subBlock);
                    blockStack.push_front(codeGenBlock);

                    genBody(blockStack, (OperatorBlock *)command, function);

                    // blockStack.front(); TODO: free up
                    blockStack.pop_front();
                    break;
                }
                default : {
                    std::cout << "Unexpected node type "
                        << command->getClassName()
                        << std::endl;
                    break;
                }
            }
        }
    }


    void genExpr(std::deque<CodeGenBlock *> & blockStack, Expression * expr) {
        //TODO: implement
    }


    void genIf(std::deque<CodeGenBlock *> & blockStack, Conditional * conditional, Function * function) {
        BasicBlock * curBlock = blockStack.front()->block;

        Expression * cond = (Expression*) conditional->children[0];
        llvm::Value * conditionValue = getLLVMExprValue(blockStack, cond);

        if (!conditionValue) {
            std::cout << "Error generating code for the condition of if " << std::endl;
            cond->print();
            std::cout << std::endl;
            return;
        }

        // then block
        OperatorBlock * thenNode = (OperatorBlock*) conditional->children[1];
        BasicBlock* thenBlock;
        thenBlock = BasicBlock::Create(context, "", function, 0);

        CodeGenBlock * thenCodeBlock = new CodeGenBlock(thenBlock);
        blockStack.push_front(thenCodeBlock);
        genBody(blockStack, thenNode, function);
        blockStack.pop_front();

        // else block
        if (conditional->children.size() == 3) { // there is else branch
            OperatorBlock * elseNode = (OperatorBlock*) conditional->children[2];
            BasicBlock * elseBlock;
            elseBlock = BasicBlock::Create(context, "", function, 0);

            CodeGenBlock * elseCodeBlock = new CodeGenBlock(elseBlock);
            blockStack.push_front(elseCodeBlock);
            genBody(blockStack, elseNode, function);
            blockStack.pop_front();

            BranchInst::Create(thenBlock, elseBlock, conditionValue, curBlock);
        }
        else { // there is no else branch
            BranchInst::Create(thenBlock, nullptr, conditionValue, curBlock);
        }

    }


    void genFor(std::deque<CodeGenBlock *> & blockStack, ForLoop * forLoop) {
        //TODO: implement
    }


    void genWhile(std::deque<CodeGenBlock *> & blockStack, WhileLoop * whileLoop) {
        //TODO: implement
    }


    void genPost(std::deque<CodeGenBlock *> & blockStack, PostLoop * postLoop) {
        //TODO: implement
    }


    void genVarDecl(std::deque<CodeGenBlock *> & blockStack, VariableDecl * varDecl) {
        #ifdef VERBOSE_CODE_GEN_INFO
            std::cout << "Generating llvm code for variable declaration ";
        #endif

        // type
        TypeNode * typeNode = (TypeNode*) varDecl->children[0];
        llvm::Type * varBasicType = getLLVMType(typeNode->type);

        // name
        Identifier * identifier = (Identifier*) varDecl->children[1];
        StringValue * nameValue = (StringValue *) identifier->value;
        std::string * varName = nameValue->value;

        #ifdef VERBOSE_CODE_GEN_INFO
            std::cout << *varName << std::endl;
        #endif


        if (varDecl->children[2]) { // if array
            ArrayDim * dimen = (ArrayDim *) varDecl->children[2]; // dimensions

            // TODO: add array dimension support here

        } // else just simple variable


        Value * initValue = nullptr;
        if (varDecl->children[3]) { // init part can be absent
            Expression * initExpr = (Expression*)varDecl->children[3]; // init

            // TODO: WARN check the type more porperly !!! !!! !!!

            // can be Expression
            // can be Increment
            // can be LeftPartExpr
            // can be literal, which is expression
            // can be ArrayItems, which are expression either

            initValue = getLLVMExprValue(blockStack, initExpr);
        }

        //WARN: only simple variables supported: no array support for now

        std::map<std::string, llvm::Value *> & locals = blockStack.front()->env;
        BasicBlock * curBlock = blockStack.front()->block;

        AllocaInst * alloc = new AllocaInst(varBasicType, *varName, curBlock);
        locals[*varName] = alloc;
        blockStack.front()->varVersion[*varName] = 1;

        if (initValue) {
            new StoreInst(initValue, locals[*varName], false, curBlock);
        }
    }


    void genAssignment(std::deque<CodeGenBlock *> & blockStack, Assignment * assignment) {
        #ifdef VERBOSE_CODE_GEN_INFO
            std::cout << "Generating llvm code for assignment ";
        #endif

        // name
        LeftPartExpr * leftPartExpr = (LeftPartExpr*) assignment->children[0];
        Identifier * identifier = (Identifier*) leftPartExpr->children[0];
        StringValue * nameValue = (StringValue *) identifier->value;
        std::string * varName = nameValue->value;

        #ifdef VERBOSE_CODE_GEN_INFO
            std::cout << *varName << std::endl;
        #endif

        if (leftPartExpr->children[1]) { // if array
            ArrayDim * dimen = (ArrayDim *) leftPartExpr->children[1]; // dimensions

            // TODO: add array dimension support here

        } // else just simple variable


        Value * initValue = nullptr;
        if (assignment->children[1]) { // init part can be absent
            Expression * initExpr = (Expression*)assignment->children[1]; // init

            // TODO: WARN check the type more porperly !!! !!! !!!

            // can be Expression
            // can be Increment
            // can be LeftPartExpr
            // can be literal, which is expression
            // can be ArrayItems, which are expression either

            initValue = getLLVMExprValue(blockStack, initExpr);
        }

        //WARN: only simple variables supported: no array support for now

        std::map<std::string, llvm::Value *> & locals = blockStack.front()->env;
        BasicBlock * curBlock = blockStack.front()->block;

        llvm::Value * val = getVariableValue(blockStack, varName);

        blockStack.front()->varVersion[*varName]++;
        int varVersion = blockStack.front()->varVersion[*varName];
        std::string * newName = new std::string(*varName + std::to_string(varVersion));

        llvm::Type * varType = ((AllocaInst*) locals[*varName])->getAllocatedType();
        AllocaInst * alloc = new AllocaInst(varType, *newName, blockStack.front()->block);

        locals[*newName] = alloc;

        if (initValue) {
            new StoreInst(initValue, locals[*newName], false, curBlock);
        }
    }


    void genFunCall(std::deque<CodeGenBlock *> & blockStack, FunctionCall * funCall) {
        //TODO: implement
    }


    void genContinue(std::deque<CodeGenBlock *> & blockStack) {
        //TODO: implement
    }


    void genBreak(std::deque<CodeGenBlock *> & blockStack) {
        //TODO: implement
    }


    void genInc(std::deque<CodeGenBlock *> & blockStack, Increment * increment) {
        //TODO: implement
    }


    Value * getLLVMExprValue(std::deque<CodeGenBlock *> & blockStack, Expression * expr) {
        #ifdef VERBOSE_CODE_GEN_INFO
            std::cout << "Generating LLVM code for expression" << std::endl;
            expr->print();
            std::cout << std::endl;
        #endif

        if (expr->getClassName() == "BinaryExpr") {
            Value * lVal = getLLVMExprValue(blockStack, (Expression*) expr->children[0]);
            Value * rVal = getLLVMExprValue(blockStack, (Expression*) expr->children[1]);

            BasicBlock * curBlock = blockStack.front()->block;

            // TODO: implement operand type pulling
            // NOTE: for now it's just int operations supported

            BinOp * op = (BinOp*)expr->value;
            Instruction::BinaryOps llvmOp;

            switch (op->tokenType) {
                case TTAND:
                    llvmOp = Instruction::And;
                    break;
                case TTOR:
                    llvmOp = Instruction::Or;
                    break;

                case TTPLUS:
                    llvmOp = Instruction::Add;
                    break;
                case TTMINUS:
                    llvmOp = Instruction::Sub;
                    break;
                case TTMULT:
                    llvmOp = Instruction::Mul;
                    break;
                case TTDIV:
                    llvmOp = Instruction::SDiv;
                    break;
                default: {
                    llvm::CmpInst::Predicate predicate;
                    switch (op->tokenType) {
                        case TTEQ:
                            predicate = llvm::CmpInst::ICMP_EQ;
                            break;
                        case TTNEQ:
                            predicate = llvm::CmpInst::ICMP_NE;
                            break;
                        case TTGT:
                            predicate = llvm::CmpInst::ICMP_SGT; ///< signed greater than
                            break;
                        case TTLT:
                            predicate = llvm::CmpInst::ICMP_SLT; ///< signed less than
                            break;
                        case TTGE:
                            predicate = llvm::CmpInst::ICMP_SGE; ///< signed greater or equal
                            break;
                        case TTLE:
                            predicate = llvm::CmpInst::ICMP_SLE; ///< signed less or equal
                            break;
                        default: {
                            std::cout
                                << "No matching binary operator "
                                << op->getValue()
                                << std::endl;
                            return nullptr;
                        }
                    }
                    return new ICmpInst(*curBlock, predicate, lVal, rVal, "");
                }
            }
            return BinaryOperator::Create(llvmOp, lVal, rVal, "", curBlock);
        } // binary expr

        else if (expr->getClassName() == "UnaryExpr") {
            Value * subExp = getLLVMExprValue(blockStack, (Expression*) expr->children[0]);
            UnOp * op = (UnOp *)expr->value;
            //TODO: implement
            return nullptr;
        } // UnaryExpr

        else if (expr->getClassName() == "Literal") {
            if (expr->value->getClassName() == "IntValue") {
                int value = ((IntValue *)expr->value)->value;
                return ConstantInt::get(Type::getInt32Ty(context), value, true);
            }
            else if (expr->value->getClassName() == "CharValue") {
                //TODO: implement
                return nullptr;
            }
            else if (expr->value->getClassName() == "StringValue") {
                //TODO: implement
                return nullptr;
            }
            else if (expr->value->getClassName() == "FloatValue") {
                //TODO: implement
                return nullptr;
            }
            else if (expr->value->getClassName() == "BoolValue") {
                if (((BoolValue *)expr->value)->value) {
                    return ConstantInt::getTrue(context);
                }
                else {
                    return ConstantInt::getFalse(context);
                }
            }
        } // literal

        else if (expr->getClassName() == "FunctionCall") {
            //TODO: implement
            return nullptr;
        } // FunctionCall

        else if (expr->getClassName() == "LeftPartExpr") {

            //TODO: add array indexing support

            StringValue * nameValue = (StringValue*)expr->children[0]->value;
            std::string * name = nameValue->value;

            llvm::Value * varValue = getVariableValue(blockStack, name);

            if (varValue == nullptr) {
               std::cout << "Undeclared variable " << *name << std::endl;
               return nullptr;
            }
            BasicBlock * curBlock = blockStack.front()->block;
            return new LoadInst(varValue, "", false, curBlock);
        } // LeftPartExpr

        else if (expr->getClassName() == "Increment") {
            Expression * subExprNode = (Expression*) expr->children[0];
            Value * subExp = getLLVMExprValue(blockStack, subExprNode);
            //TODO: implement
            return nullptr;
        } // Increment

        else if (expr->getClassName() == "ArrayItems") {
            //TODO: implement
            return nullptr;
        } // ArrayItems

        std::cout
            << "No matching node class for AST node "
            << expr->getClassName()
            << std::endl;

        return nullptr;
    }


};

#endif // CODEGEN
