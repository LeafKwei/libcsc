#include "dbc/syntax/cmds.hpp"
DBC_BEGIN

//============== CommonCmd =============
CommonCmd::CommonCmd(std::initializer_list<OperandType> types) : m_typeList(types){}

int CommonCmd::tokenNumber(){
    return typeList().size();
}

Policy CommonCmd::run(const std::vector<Token> &tokens, Dcontext &context){
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

Policy EnterDomainCmd::run(const std::vector<Token> &tokens, Dcontext &context){
    if(!isThisType(tokens)) return Policy::Missed;
    
    auto &name = tokens[0].buffer;

    if(context.existsDomain(name)){
         context.enterDomain(name);
    }
    else{
        context.makeDomain(name);
        context.enterDomain(name);
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

Policy ExitDomainCmd::run(const std::vector<Token> &tokens, Dcontext &context){
    if(!isThisType(tokens)) return Policy::Missed;
    
    auto &name = tokens[1].buffer;

    if(name != context.path()){
        return Policy::Bad;
    }

    try{
        context.exitDomain();
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

Policy AssignCmd::run(const std::vector<Token> &tokens, Dcontext &context){
    if(!isThisType(tokens)) return Policy::Missed;

    context.set(tokens[0].buffer, tokens[2].buffer);
    return Policy::Accepted;
}

bool AssignCmd::isLegalToken(const std::vector<Token> &tokens){
    auto &opt = tokens[1].buffer;
    auto &value = tokens[2].buffer;

    return (opt == "=");
}

DBC_END