#include "csc/lex/Lexer.hpp"
#include "csc/syntax/Operand.hpp"
CSC_BEGIN

Operand::Operand(const Token &token) : m_token(token){
    updateValueType();
    updateOperandType(); //此函数会依赖ValueType，因此请确保此函数在updateValueType之后调用
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
    m_optype = getOperandTypeof(m_token, m_valtype);
}

ValueType Operand::getValueTypeof(const Token &token){
        switch(token.type){
        case TokenType::Keyword:
            return (token.str == "true" || token.str == "false") ? ValueType::Bool : ValueType::Unknown;
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

ValueType Operand::getArrayValueTypeof(const Token &token){
    Lexer lexer(token.str);
    const auto &tk = lexer.nextResult();
    return getValueTypeof(tk.token);
}

OperandType Operand::getOperandTypeof(const Token &token, ValueType type){
        switch(type){
        case ValueType::Bool:
        case ValueType::Integer:
        case ValueType::Double:
        case ValueType::String:
            return OperandType::Value;
        default:
            return getOtherOperandTypeof(token);
    }
}

/* 负责处理通过ValueType无法确定其OperandType的其他token */
OperandType Operand::getOtherOperandTypeof(const Token &token){
        switch(token.type){
        case TokenType::Keyword:
            return (m_valtype == ValueType::Bool) ? OperandType::Value : OperandType::Keyword;
        case TokenType::Array:
            return OperandType::Values;
        case TokenType::Identifier:
            return OperandType::Identifier;
        case TokenType::Operator:
            return OperandType::Operator;
        default:
            return OperandType::Unknown;
    }
}


CSC_END