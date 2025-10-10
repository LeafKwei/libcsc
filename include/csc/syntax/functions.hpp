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
    switch(token.type){
        case TokenType::Keyword:
            if(token.str == KW_TRUE || token.str == KW_FALSE) return OperandType::Value;   //对于关键字true和false，将其作为值处理
            return OperandType::Keyword;
        case TokenType::Number:
        case TokenType::String:
            return OperandType::Value;
        case TokenType::Array:
            return OperandType::Values;
        default:
            return OperandType::Unknown;
    }
}

/* 将Token类型转换为供Context使用的Value类型 */
inline ValueType valueTypeof(const Token &token){
    switch(token.type){
        case TokenType::Number:
            if(token.tag == TokenTag::Float) return ValueType::Double;
            return ValueType::Integer;
        case TokenType::String:
            return ValueType::String;
        case TokenType::Keyword:
            if(token.str == KW_TRUE || token.str == KW_FALSE)
                return ValueType::Bool;
            return ValueType::Unknown;
        default:
            return ValueType::Unknown;
    }
}

/* 将数组Token转换为供Context使用的Value类型 */
inline ValueType arrayTypeof(const Token &token){
    CharMngr mngr(token.str);
    PureLexer lexer;
    return valueTypeof(lexer.nextResultFrom(mngr));
}

 /** 
  * 首先将token类型转换为operand类型，然后根据operand类型决定key item的生成。对应Keyword、Operator这些与Command对象绑定的类型,
  * 以token.str中的字符串作为key item，对于Identifer、Value这些与Command对象无关的类型，则以它们的枚举值作为key item。
  */
inline String tokenToKeyItem(const Token &token){
    std::stringstream sstream;
    auto op = operandTypeof(token);

    switch(op){
        case OperandType::Identifier:
            sstream << static_cast<int>(OperandType::Identifier);
            break;
        case OperandType::Keyword:
            sstream << token.str;
            break;
        case OperandType::Operator:
            sstream << token.str;
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

inline Value tokenToValue(const Token &token, ValueType type){
    switch(type){
        case ValueType::Bool:
            if(token.str == KW_TRUE) return true;
            return false;
        case ValueType::Integer:
            int base = (token.tag == TokenTag::Hex) ? 16 : 10;
            return strtol(token.str.c_str(), NULL, base);
        case ValueType::Double:
            return strtod(token.str.c_str(), NULL);
        case ValueType::String:
            return token.str;
        default:
            return "";
    }
};

CSC_END
#endif