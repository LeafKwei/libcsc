#include <iostream>
#include <sstream>
#include "csc/context/val.hpp"
#include "csc/syntax/opr.hpp"
#include "csc/syntax/Operand.hpp"
CSC_BEGIN

Operand::Operand(TokenHolder &holder){
    initOperand(holder);
    initValue(holder);
}

String Operand::key() const noexcept{
    return key_;
}

Operand::Type Operand::type() const noexcept{
    return type_;
}

Size_t Operand::size() const noexcept{
    return valueunits_.size();
}

String Operand::stringvalue(int index) const{
    return std::any_cast<String>(valueunits_.at(index).value);
}

ValueUnit Operand::value(int index) const{
    return valueunits_.at(index);
}

Operand::ValueUnitCR Operand::refervalue(int index) const{
    return valueunits_.at(index);
}

void Operand::initOperand(TokenHolder &holder){
    initType(holder);  //initType放在最开始，以便提前调用holder.token函数对token是否为空进行断言
    initKey(holder);
}

void Operand::initValue(TokenHolder &holder){
    switch(type_){
        /* 对于整数、浮点数等值类型的操作数，将它们按照对应类型生成值 */
        case OperandType::Value:
        case OperandType::Values:
            initValidValue(holder);
            break;
        /* 对于操作符、关键字等非值类型的操作数，将它们统一生成为字符串类的值，方便后续其他功能模块可以用同一套接口访问  */
        default:
            initNonValidValue(holder);
    }
}

void Operand::initValidValue(TokenHolder &holder){
    auto size = holder.size();

    for(decltype(size) i = 0; i < size; i++){
        auto type = valueTypeof(holder.token(i));
        valueunits_.push_back(
            ValueUnit{
                makeValueFrom(holder.token(i), type),
                type
            }
        );
    }
}

void Operand::initNonValidValue(TokenHolder& holder){
    valueunits_.push_back(
        ValueUnit{
            holder.token().str,
            ValueType::String
        }
    );
}

void Operand::initType(TokenHolder &holder){
    auto type = operandTypeOf(holder.token());

    /* 如果token转换得到的OperandType是Value类型，那么根据Holder内的token数量是否是复数决定此Operand的类型是否是Values类型 */
    if(type == OperandType::Value && holder.plural()){
        type_ = OperandType::Values;
        return;
    }

    type_ = type;
}

void Operand::initKey(TokenHolder &holder){
    key_ = genKeyFrom(type_, holder.token().str);   
}

CSC_END