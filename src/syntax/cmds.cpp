#include "csc/syntax/cmds.hpp"
#include "csc/syntax/functions.hpp"
CSC_BEGIN

//============== CommonCmd =============
CommonCmd::CommonCmd(InitOpTypes types) : m_types(types){}

int CommonCmd::tokenNumber(){
    return typeList().size();
}

Policy CommonCmd::run(ConstTokenList tokens, Context &context){
    return Policy::Missed;
}

CommonCmd::ConstOpTypeList CommonCmd::typeList(){
    return m_types;
}

bool CommonCmd::isThisType(ConstTokenList tokens){
    int index = 0;
    auto types = typeList();

    if(tokens.size() != types.size()) return false;

    for(auto type : types){
        if(toOperandType(tokens.at(index)) != type) return false;
        ++index;
    }

    return isLegalToken(tokens);
}

bool CommonCmd::isLegalToken(ConstTokenList tokens){
    return false;
}

//============== EnterScopeCmd =============
EnterScopeCmd::EnterScopeCmd() : CommonCmd(
    {OperandType::Identifier, OperandType::Operator}
){}

Policy EnterScopeCmd::run(ConstTokenList tokens, Context &context){
    if(!isThisType(tokens)) return Policy::Missed;
    
    auto &name = tokens[0].buffer;
    
    if(context.probeScope(name)){
         context.enterScope(name);
    }
    else{
        context.makeScope(name, true);
    }

    return Policy::Accepted;
}

bool EnterScopeCmd::isLegalToken(ConstTokenList tokens){
    return tokens[1].buffer == "::";
}

//============== ExitScopeCmd =============
ExitScopeCmd::ExitScopeCmd() : CommonCmd(
    {OperandType::Operator, OperandType::Identifier}
){}

Policy ExitScopeCmd::run(ConstTokenList tokens, Context &context){
    if(!isThisType(tokens)) return Policy::Missed;
    
    auto &name = tokens[1].buffer;

    if(name != context.scopeName()){
        return Policy::Bad;
    }

    try{
        context.leaveScope();
        return Policy::Accepted;
    }
    catch(ContextExcept &e){
        return Policy::Bad;
    }
}

bool ExitScopeCmd::isLegalToken(ConstTokenList tokens){
    return tokens[0].buffer == "::";
}

//============== AssignCmd =============
AssignCmd::AssignCmd() : CommonCmd(
    {OperandType::Identifier, OperandType::Operator, OperandType::Value}
){}

Policy AssignCmd::run(ConstTokenList tokens, Context &context){
    if(!isThisType(tokens)) return Policy::Missed;

    auto vtype = toValueType(tokens[2]);
    if(vtype == ValueType::Unknown) return Policy::Bad;

    context.makeVariable(tokens[0].buffer, tokens[2].buffer, vtype);
    return Policy::Accepted;
}

bool AssignCmd::isLegalToken(ConstTokenList tokens){
    return (tokens[1].buffer == "=");
}

//============== ArrayAssignCmd =============
ArrayAssignCmd::ArrayAssignCmd() : CommonCmd(
    {OperandType::Identifier, OperandType::Operator, OperandType::Values}
){}

Policy ArrayAssignCmd::run(ConstTokenList tokens, Context &context){
    if(!isThisType(tokens)) return Policy::Missed;

    auto vtype = toValueType(tokens[2]);
    if(vtype == ValueType::Unknown) return Policy::Bad;
    context.makeVariable(tokens[0].buffer, "", vtype);

    auto &name = tokens[0].buffer;
    TokenType type = TokenType::Unexcepted;
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
            
            return Policy::Bad;
        }

        if(toOperandType(token) != OperandType::Value){
            return Policy::Bad; 
        }

        if(type != TokenType::Unexcepted && type != token.type){  //If elements in array is not a same type.
            return Policy::Bad;
        }

        context.extendValues(name, {token.buffer});
        type = token.type;
    }

    return Policy::Accepted;
}

bool ArrayAssignCmd::isLegalToken(ConstTokenList tokens){
    return (tokens[1].buffer == "=");
}

CSC_END