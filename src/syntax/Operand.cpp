#include <iostream>
#include <sstream>
#include "csc/utility/utility.hpp"
#include "csc/syntax/Operand.hpp"
CSC_BEGIN

Operand::Operand(const Token &token) : m_token(token), m_maker(token){
    updateOperandType();
}

crString Operand::str() const noexcept{
    return m_token.str;
}
Operand::crToken Operand::token() const noexcept{
    return m_token;
}

TokenType Operand::typeofToken() const noexcept{
    return m_token.type;
}

OperandType Operand::typeofOperand() const noexcept{
    return m_type;
}

ValueType Operand::typeofValue() const noexcept{
    return m_maker.type();
}

Value Operand::value() const{
    return m_maker.value();
}

/* 根据Operand生成对应的key，这些key最终将用于合成一个key序列，以该序列代表一组Operand，并用于匹配一个对应的Command */
String Operand::key() const{
    std::stringstream sstream;
    auto type = m_type;
    auto &token = m_token;

    switch(type){
        case OperandType::Identifier:
            sstream << static_cast<int>(type);
            break;
        case OperandType::Keyword:
            sstream << token.str;
            break;
        case OperandType::Operator:
            sstream << token.str;
            break;
        case OperandType::Value:
            sstream << static_cast<int>(type);
            break;
        case OperandType::Values:
            sstream << static_cast<int>(type);
            break;
        default:
            sstream << "*** BAD OPERAND  ***";
    }

    return sstream.str();
}

void Operand::updateOperandType(){
    m_type = (m_token.type != TokenType::Array) ? getOperandTypeof(m_token) : OperandType::Values;
}

OperandType Operand::getOperandTypeof(const Token &token) const{
    switch(token.type){
        case TokenType::String:
        case TokenType::Number:
            return OperandType::Value;
        case TokenType::Keyword:
            return (isBoolString(token.str)) ? OperandType::Value : OperandType::Keyword;
        case TokenType::Identifier:
            return OperandType::Identifier;
        case TokenType::Operator:
            return OperandType::Operator;
        default:
            return OperandType::Unknown;
    }
}

CSC_END