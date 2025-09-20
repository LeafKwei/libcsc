#include "csc/syntax/commands.hpp"
#include "csc/syntax/functions.hpp"
#include "csc/lex/PureLexer.hpp"
CSC_BEGIN

//============== CommonCmd =============
CommonCmd::CommonCmd(InitOpTypes types) : m_types(types){}

Size_t CommonCmd::sizeofTypes(){
    return m_types.size();
}

CommonCmd::OpType  CommonCmd::opTypeAt(int index){
    return m_types.at(index);
}

//============== EnterScopeCmd =============
EnterScopeCmd::EnterScopeCmd() : CommonCmd(
    {OperandType::Identifier, OperandType::Operator}
){}

bool EnterScopeCmd::runnable(const TokenList &tokens){
    return tokens.at(1).buffer == "::";
}

void EnterScopeCmd::run(const TokenList &tokens, Context &context){
    auto &name = tokens[0].buffer;
    
    if(context.probeScope(name)){
         context.enterScope(name);
    }
    else{
        context.makeScope(name, true);
    }
}

//============== ExitScopeCmd =============
ExitScopeCmd::ExitScopeCmd() : CommonCmd(
    {OperandType::Operator, OperandType::Identifier}
){}

bool ExitScopeCmd::runnable(const TokenList &tokens){
    return tokens.at(0).buffer == "::";
}

void ExitScopeCmd::run(const TokenList &tokens, Context &context){
    auto &name = tokens[1].buffer;

    if(name != context.scopeName()){
        throw CommandExcept("Can't leave a scope that name is not same to current scope.");
    }

    context.leaveScope();
}

//============== AssignCmd =============
AssignCmd::AssignCmd() : CommonCmd(
    {OperandType::Identifier, OperandType::Operator, OperandType::Value}
){}

bool AssignCmd::runnable(const TokenList &tokens){
    return tokens.at(1).buffer == "=";
}

void AssignCmd::run(const TokenList &tokens, Context &context){
    auto vtype = valueTypeof(tokens[2]);
    if(vtype == ValueType::Unknown) throw CommandExcept("Invalid value in assignment.");

    context.makeVariable(tokens[0].buffer, tokens[2].buffer, vtype);
}

//============== ArrayAssignCmd =============
ArrayAssignCmd::ArrayAssignCmd() : CommonCmd(
    {OperandType::Identifier, OperandType::Operator, OperandType::Values}
){}

bool ArrayAssignCmd::runnable(const TokenList &tokens){
    return tokens.at(1).buffer == "=";
}

void ArrayAssignCmd::run(const TokenList &tokens, Context &context){
    auto vtype = valueTypeof(tokens[2]);
    if(vtype == ValueType::Unknown) throw CommandExcept("Invalid value in assignment.");
    context.makeVariable(tokens[0].buffer, "", vtype);

    auto &name = tokens[0].buffer;
    auto etype = ValueType::Unknown;
    CharMngr mngr(tokens[2].buffer);
    PureLexer lexer;

    while(mngr.valid()){
        auto token = lexer.nextTokenFrom(mngr);

        if(token.type == TokenType::Aborted){
            break;
        }

        if(token.type == TokenType::Unexcepted){
            if(mngr.getch() ==','){
                mngr.forward();
                continue;
            }
            
            throw CommandExcept("Invalid character in assignment.");
        }

        if(operandTypeof(token) != OperandType::Value){
            throw CommandExcept("Invalid token in assignment.");
        }

        auto cetype = valueTypeof(token);
        if(etype != ValueType::Unknown && etype != cetype){  /* 如果数组中的元素类型不同则视为错误 */
            throw CommandExcept("Elements in array are not a same type.");
        }

        context.extendValues(name, {token.buffer});
        etype = cetype;
    }
}

CSC_END