#ifndef CSC_SYNTAX_FUNCIONS_HPP
#define CSC_SYNTAX_FUNCIONS_HPP

#include <iostream>
#include <sstream>
#include "csc/lex/types.hpp"
#include "csc/syntax/types.hpp"
#include "csc/context/types.hpp"
#include "csc/syntax/Operand.hpp"
CSC_BEGIN

 /** 
  * 首先将token类型转换为operand类型，然后根据operand类型决定key item的生成。对应Keyword、Operator这些与Command对象绑定的类型,
  * 以token.str中的字符串作为key item，对于Identifer、Value这些与Command对象无关的类型，则以它们的枚举值作为key item。
  */
inline String tokenToKeyItem(const Token &token){
    std::stringstream sstream;
    Operand operand(token);
    auto type = operand.typeofOperand();

    switch(type){
        case OperandType::Identifier:
            sstream << static_cast<int>(type);
            break;
        case OperandType::Keyword:
            sstream << operand.str();
            break;
        case OperandType::Operator:
            sstream << operand.str();
            break;
        case OperandType::Value:
            sstream << static_cast<int>(type);
            break;
        case OperandType::Values:
            sstream << static_cast<int>(type);
            break;
        default:
            sstream << "BadOpType";
    }

    return sstream.str();
}

CSC_END
#endif