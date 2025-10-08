#include "csc/syntax/Operand.hpp"
CSC_BEGIN

Operand::Operand(const Token &token) : m_token(token){
    updateOperandType();
    updateValueType();           //此函数会依赖OperandType，因此请确保此函数在updateOperandType之后调用
}

crString Operand::str() const noexcept{
    return m_token.str;
}
Operand::crToken Operand::token() const noexcept{
    return m_token;
}

TokenType Operand::tokenType() const noexcept{
    return m_token.type;
}

OperandType Operand::operandType() const noexcept{
    return m_optype;
}

ValueType Operand::valueType() const noexcept{
    return m_valtype;
}

Value Operand::value() const{

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

void Operand::updateOperandType(){

}

void Operand::updateValueType(){

}

CSC_END