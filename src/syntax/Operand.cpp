#include <iostream>
#include <sstream>
#include "csc/lex/Lexer.hpp"
#include "csc/lex/initializers.hpp"
#include "csc/syntax/Operand.hpp"
CSC_BEGIN

Operand::Operand(const Token &token) : m_token(token){
    updateValueType();
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
    return m_optype;
}

ValueType Operand::typeofValue() const noexcept{
    return m_valtype;
}

Value Operand::value() const{
    switch(m_valtype){
        case ValueType::Bool:
            if(m_token.str == "true") return CppType<ValueType::Bool>::type{true};
            return CppType<ValueType::Bool>::type{false};
        //------------------------------------------------------
        case ValueType::Integer:
            if(m_token.tag == TokenTag::Hex){                        //当Token含有16进制标签时，按16进制转换
                return CppType<ValueType::Integer>::type{
                    strtol(m_token.str.c_str(), NULL, 16)};
            }
            return  CppType<ValueType::Integer>::type{       //否则按10进制转换
                    strtol(m_token.str.c_str(), NULL, 10)};
        //------------------------------------------------------
        case ValueType::Double:
            return CppType<ValueType::Double>::type{strtod(m_token.str.c_str(), NULL)};
        //------------------------------------------------------
        case ValueType::String:
            return CppType<ValueType::String>::type{m_token.str};
        //------------------------------------------------------
        default:
            return Value{};
    }
}

Value Operand::zero() const{
    return zero(m_valtype);
}

Value Operand::zero(ValueType type){
    switch(type){
        case ValueType::Bool:
            return CppType<ValueType::Bool>::type{};
        case ValueType::Integer:
            return CppType<ValueType::Integer>::type{};
        case ValueType::Double:
            return CppType<ValueType::Double>::type{};
        case ValueType::String:
            return CppType<ValueType::String>::type{};
        default:
            return Value{};
    }
}

void Operand::updateValueType(){
    if(m_token.type != TokenType::Array)
        m_valtype = getValueTypeof(m_token);
    else
        m_valtype = getArrayValueTypeof(m_token);  //对于数组类token，需要先用Lexer分解成单个元素后再判断类型
}

void Operand::updateOperandType(){
    if(m_token.type != TokenType::Array)
        m_optype = getOperandTypeof(m_token);
    else
        m_optype = OperandType::Values;
}

ValueType Operand::getValueTypeof(const Token &token) const{
        switch(token.type){
        case TokenType::Keyword:
            return (isBoolString(token.str)) ? ValueType::Bool : ValueType::Unknown;
        case TokenType::Number:
            if(token.tag == TokenTag::Float)
                return ValueType::Double;
            else
                return ValueType::Integer;
        case TokenType::String:
            return ValueType::String;
        default:
            return ValueType::Unknown;
    }
}

ValueType Operand::getArrayValueTypeof(const Token &token) const{
    CharMngr mngr(token.str);
    PureLexer lexer;
    arraylexer_initializer(lexer);

    const auto &tk = lexer.nextResultFrom(mngr);
    return getValueTypeof(tk.token);
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

bool Operand::isBoolString(crString str) const{
    return (str == "true") || (str == "false");
}
 
/* 根据Operand生成对应的key，这些key最终将用于合成一个key序列，以该序列代表一组Operand，并用于匹配一个对应的Command */
String Operand::key() const{
    std::stringstream sstream;
    auto type = m_optype;
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

CSC_END