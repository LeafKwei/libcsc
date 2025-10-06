#ifndef CSC_SYNTAX_FUNCIONS_HPP
#define CSC_SYNTAX_FUNCIONS_HPP

#include <iostream>
#include <sstream>
#include "csc/lex/types.hpp"
#include "csc/lex/PureLexer.hpp"
#include "csc/syntax/types.hpp"
#include "csc/context/types.hpp"
CSC_BEGIN

/* 将Token类型转换为供sytanx内的类使用的Operand类型，对一些Token类型进行聚合 */
inline OperandType operandTypeof(const Token &token){

}

CSC_INNER_BEGIN
/* 将Token类型转换为供Context使用的Value类型 */
inline ValueType valueTypeofHelper(const Token &token){

}

CSC_INNER_END

/* 将Token类型转换为供Context使用的Value类型，借助valueTypeofHelper对数组Token进行类型判断 */
inline ValueType valueTypeof(const Token &token){

}

 /** 
  * 首先将token类型转换为operand类型，然后根据operand类型决定key item的生成。对应Keyword、Operator这些与Command对象绑定的类型，
  * 以token.buffer中的字符串作为key item，对于Identifer、Value这些与Command对象无关的类型，则以它们的枚举值作为key item。
  */
inline String tokenToKeyItem(const Token &token){
    std::stringstream sstream;
    auto op = operandTypeof(token);

    switch(op){
        case OperandType::Identifier:
            sstream << static_cast<int>(OperandType::Identifier);
            break;
        case OperandType::Keyword:
            sstream << token.buffer;
            break;
        case OperandType::Operator:
            sstream << token.buffer;
            break;
        case OperandType::Value:
            sstream << static_cast<int>(OperandType::Value);
            break;
        case OperandType::Values:
            sstream << static_cast<int>(OperandType::Values);
            break;
        default:
            sstream << "BadOpType";
    }

    return sstream.str();
}

CSC_END
#endif