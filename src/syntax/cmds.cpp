#include "csc/syntax/cmds.hpp"
#include "csc/syntax/functions.hpp"
CSC_BEGIN

//============== CommonCmd =============
CommonCmd::CommonCmd(std::initializer_list<OperandType> types) : m_typeList(types){}

int CommonCmd::tokenNumber(){
    return typeList().size();
}

Policy CommonCmd::run(const std::vector<Token> &tokens, Context &context){
    return Policy::Missed;
}

const std::vector<OperandType>& CommonCmd::typeList(){
    return m_typeList;
}

bool CommonCmd::isThisType(const std::vector<Token> &tokens){
    int index = 0;
    auto types = typeList();

    if(tokens.size() != types.size()) return false;

    for(auto type : types){
        if(toOperandType(tokens.at(index)) != type) return false;
        ++index;
    }

    return isLegalToken(tokens);
}

bool CommonCmd::isLegalToken(const std::vector<Token> &tokens){
    return false;
}

//============== EnterDomainCmd =============
EnterDomainCmd::EnterDomainCmd() : CommonCmd(
    {OperandType::Identifier, OperandType::Operator}
){}

Policy EnterDomainCmd::run(const std::vector<Token> &tokens, Context &context){
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

bool EnterDomainCmd::isLegalToken(const std::vector<Token> &tokens){
    return tokens[1].buffer == "::";
}

//============== ExitDomainCmd =============
ExitDomainCmd::ExitDomainCmd() : CommonCmd(
    {OperandType::Operator, OperandType::Identifier}
){}

Policy ExitDomainCmd::run(const std::vector<Token> &tokens, Context &context){
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

bool ExitDomainCmd::isLegalToken(const std::vector<Token> &tokens){
    return tokens[0].buffer == "::";
}

//============== AssignCmd =============
AssignCmd::AssignCmd() : CommonCmd(
    {OperandType::Identifier, OperandType::Operator, OperandType::Value}
){}

Policy AssignCmd::run(const std::vector<Token> &tokens, Context &context){
    if(!isThisType(tokens)) return Policy::Missed;

    context.makeVariable(tokens[0].buffer, tokens[2].buffer, toValueType(tokens[2]));
    return Policy::Accepted;
}

bool AssignCmd::isLegalToken(const std::vector<Token> &tokens){
    auto &opt = tokens[1].buffer;
    auto &value = tokens[2].buffer;

    return (opt == "=");
}

CSC_END