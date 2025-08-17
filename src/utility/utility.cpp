#include "dbc/lex/types.hpp"
#include "dbc/utility/utility.hpp"
#include <algorithm>

DBC_BEGIN

Dstring join(Dstring splitor, const std::vector<Dstring> &elements, const std::initializer_list<Dstring> &filters){
    Dstring result;

    for(int idx = 0; idx < elements.size(); idx++){
        auto &e = elements.at(idx);
        result = result + e;
        if(idx + 1 >= elements.size()) continue;                                             //Don't put splitor if 'e' is last element.
        if(std::find(filters.begin(), filters.end(), e) != filters.end()) continue;   //Don't put splitor if 'e' is in filter.
        result = result + splitor;
    }

    return result;
}

int baseOf(const Dstring &str){
    if(str.substr(0, 2) == "0x") return 16;
    return 10;
}

OperandType toOperandType(const Token &token){
    switch(token.type){
        case TokenType::Identifier:
            return OperandType::Identifier;

        case TokenType::Keyword:
            if(token.buffer == "true" || token.buffer == "false")
                return OperandType::Value;
            return OperandType::Unexcepted;

        case TokenType::Operator:
            return OperandType::Operator;

        case TokenType::Number:
        case TokenType::String:
        case TokenType::Array:
            return OperandType::Value;

        default:
            return OperandType::Unexcepted;
    }
}

DBC_END