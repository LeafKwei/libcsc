#include <iostream>
#include <sstream>
#include "csc/syntax/opr.hpp"
CSC_BEGIN

String genKeyFrom(OperandType type, const String &str){
    std::stringstream sstream;

    switch(type){
        case OperandType::Value:
        case OperandType::Values:
        case OperandType::Identifier:
            sstream << static_cast<int>(type);
            break;
        case OperandType::Keyword:
        case OperandType::Operator:
            sstream << str;
            break;
        default:
            sstream << "*** BAD OPTYPE ***";
    }

    return sstream.str();
}

OperandType operandTypeOf(const Token &token){
    switch(token.type){
        case TokenType::Integer:
        case TokenType::HexInteger:
        case TokenType::Float:
        case TokenType::String:
            return OperandType::Value;
        case TokenType::Keyword:
            return (token.str == "true" || token.str == "false") ? OperandType::Value : OperandType::Keyword;
        case TokenType::Identifer:
            return OperandType::Identifier;
        case TokenType::Operator:
            return OperandType::Operator;
        default:
            return OperandType::Unknown;
    }
}

CSC_END