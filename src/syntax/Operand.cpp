#include <iostream>
#include <sstream>
#include "csc/syntax/opr.hpp"
#include "csc/syntax/Operand.hpp"
CSC_BEGIN

Operand::Operand(const TokenHolder &holder) : holder_(holder){
    initOperand();
}

Operand::Operand(TokenHolder &&holder) : holder_(std::move(holder)){
    initOperand();
}

Operand::Holder& Operand::holder(){
    return holder_;
}

String Operand::key() const noexcept{
    return key_;
}

Operand::Type Operand::type() const noexcept{
    return type_;
}

void Operand::initOperand(){
    initType();
    initKey();
}

void Operand::initType(){
    auto type = operandTypeOf(holder_.token());

    /* 如果token转换得到的OperandType是Value类型，那么根据Holder内的token数量是否是复数决定此Operand的类型是否是Values类型 */
    if(type == OperandType::Value && holder_.plural()){
        type_ = OperandType::Values;
        return;
    }

    type_ = type;
}

void Operand::initKey(){
    key_ = genKeyFrom(type_, holder_.token().str);   
}

CSC_END