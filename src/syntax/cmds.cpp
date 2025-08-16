#include "dbc/syntax/cmds.hpp"
DBC_BEGIN

//============== CommonCmd =============
CommonCmd::CommonCmd(std::initializer_list<TokenType> types) : m_typeList(types){}

int CommonCmd::tokenNumber(){
    return typeList().size();
}

Policy CommonCmd::run(const std::vector<Token> &tokens, Dcontext &context){
    return Policy::Missed;
}

const std::vector<TokenType>& CommonCmd::typeList(){
    return m_typeList;
}

bool CommonCmd::isThisType(const std::vector<Token> &tokens){
    int index = 0;
    auto types = typeList();

    if(tokens.size() != types.size()) return false;

    for(auto type : types){
        if(tokens.at(index).type != type) return false;
        ++index;
    }

    return isLegalToken(tokens);
}

bool CommonCmd::isLegalToken(const std::vector<Token> &tokens){
    return false;
}

//============== EnterDomainCmd =============
EnterDomainCmd::EnterDomainCmd() : CommonCmd(
    {TokenType::Identifier, TokenType::Operator}
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
    {TokenType::Operator, TokenType::Identifier}
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

//============== AssignBoolCmd =============
AssignBoolCmd::AssignBoolCmd() : CommonCmd(
    {TokenType::Identifier, TokenType::Operator, TokenType::Keyword}
){}

Policy AssignBoolCmd::run(const std::vector<Token> &tokens, Dcontext &context){
    if(!isThisType(tokens)) return Policy::Missed;

    context.set(ValueType::Bool, tokens[0].buffer, tokens[2].buffer);
    return Policy::Accepted;
}

bool AssignBoolCmd::isLegalToken(const std::vector<Token> &tokens){
    auto &opt = tokens[1].buffer;
    auto &value = tokens[2].buffer;

    return (opt == "=") && (value == "true" || value == "false");
}

//============== AssignNumberCmd =============
AssignNumberCmd::AssignNumberCmd() : CommonCmd(
    {TokenType::Identifier, TokenType::Operator, TokenType::Number}
){}

Policy AssignNumberCmd::run(const std::vector<Token> &tokens, Dcontext &context){
    if(!isThisType(tokens)) return Policy::Missed;

    context.set(ValueType::Number, tokens[0].buffer, tokens[2].buffer);
    return Policy::Accepted;
}

bool AssignNumberCmd::isLegalToken(const std::vector<Token> &tokens){
    return tokens[1].buffer == "=";
}

//============== AssignStringCmd =============
AssignStringCmd::AssignStringCmd() : CommonCmd(
    {TokenType::Identifier, TokenType::Operator, TokenType::String}
){}

Policy AssignStringCmd::run(const std::vector<Token> &tokens, Dcontext &context){
    if(!isThisType(tokens)) return Policy::Missed;

    context.set(ValueType::Bool, tokens[0].buffer, tokens[2].buffer);
    return Policy::Accepted;
}

bool AssignStringCmd::isLegalToken(const std::vector<Token> &tokens){
    return tokens[1].buffer == "=";
}

//============== AssignArrayCmd =============
AssignArrayCmd::AssignArrayCmd() : CommonCmd(
    {TokenType::Identifier, TokenType::Operator, TokenType::Array}
){}

Policy AssignArrayCmd::run(const std::vector<Token> &tokens, Dcontext &context){
    if(!isThisType(tokens)) return Policy::Missed;

    context.set(ValueType::Bool, tokens[0].buffer, tokens[2].buffer);
    return Policy::Accepted;
}

bool AssignArrayCmd::isLegalToken(const std::vector<Token> &tokens){
    return tokens[1].buffer == "=";
}


DBC_END