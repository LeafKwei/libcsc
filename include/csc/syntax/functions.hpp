#ifndef CSC_SYNTAX_FUNCIONS_HPP
#define CSC_SYNTAX_FUNCIONS_HPP

#include "csc/lex/types.hpp"
#include "csc/lex/PureLexer.hpp"
#include "csc/syntax/types.hpp"
#include "csc/context/types.hpp"
CSC_BEGIN

inline OperandType operandTypeof(const Token &token){
    switch(token.type){
        case TokenType::Identifier:
            return OperandType::Identifier;

        case TokenType::Keyword:
            if(token.buffer == "true" || token.buffer == "false")
                return OperandType::Value;
            return OperandType::Unexcepted;

        case TokenType::Operator:
            return OperandType::Operator;

        case TokenType::Number:
        case TokenType::String:
            return OperandType::Value;
        case TokenType::Array:
            return OperandType::Values;

        default:
            return OperandType::Unexcepted;
    }
}

CSC_INNER_BEGIN
inline ValueType valueTypeofHelper(const Token &token){
    //Bool
    if(token.type == TokenType::Keyword){
        if(token.buffer == "true" || token.buffer == "false"){
            return ValueType::Bool;
        }
    }

    //Integer/Double
    if(token.type == TokenType::Number){
        if(token.buffer.find('.') != String::npos){
            return ValueType::Double;
        }

        return ValueType::Integer;
    }

    //String
    if(token.type == TokenType::String){
        return ValueType::String;
    }

    return ValueType::Unknown;
}
CSC_INNER_END

inline ValueType valueTypeof(const Token &token){
    if(token.type != TokenType::Array){
        return csc_inner::valueTypeofHelper(token);
    }

    CharMngr mngr(token.buffer);
    PureLexer lexer;

    if(mngr.valid()){
        switch(csc_inner::valueTypeofHelper(lexer.nextTokenFrom(mngr))){
            case ValueType::Bool:
                return ValueType::Bools;
            case ValueType::Integer:
                return ValueType::Integers;
            case ValueType::Double:
                return ValueType::Doubles;
            case ValueType::String:
                return ValueType::Strings;
            default:
                return ValueType::Unknown;
        }
    }

    return ValueType::Unknown;
}

CSC_END
#endif