#include <iostream>
#include <sstream>
#include "csc/utility/utility.hpp"
#include "csc/syntax/Operand.hpp"
CSC_BEGIN

Operand::Operand(const TokenHolder &holder) : holder_(holder){

}

Operand::Operand(TokenHolder &&holder) : holder_(std::move(holder)){

}

const Token& Operand::token() const{

}

const Token& Operand::token(int index) const{

}

TokenType Operand::tokenType() const noexcept{

}

TokenType Operand::tokenType(int index) const{
    
}

Size_t Operand::tokenSize() const noexcept{

}

OperandType Operand::operandType() const noexcept{

}

String Operand::key() const{

}

void Operand::updateOperandType(){
    
}

OperandType Operand::getOperandTypeof(const Token &token) const{

}

CSC_END