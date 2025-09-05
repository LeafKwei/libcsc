#ifndef CSC_SYNTAX_FUNCTIONS_HPP
#define CSC_SYNTAX_FUNCTIONS_HPP

#include "csc/csc.hpp"
#include "csc/types.hpp"
#include "csc/lex/types.hpp"
#include "csc/core/types.hpp"
#include "csc/syntax/types.hpp"
#include "csc/context/types.hpp"
#include "csc/lex/PureLexer.hpp"
CSC_BEGIN

inline OperandType toOperandType(const Token &token){
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

inline ValueType toValueTypeHelper(const Token &token){
    //Bool
    if(token.type == TokenType::Keyword){
        if(token.buffer == "true" || token.buffer == "false"){
            return ValueType::Bool;
        }
    }

    //Integer/Double
    if(token.type == TokenType::Number){
        if(token.buffer.find('.') != CscStr::npos){
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

inline ValueType toValueType(const Token &token){
    if(token.type != TokenType::Array){
        return toValueTypeHelper(token);
    }

    CharMngr mngr(token.buffer);
    PureLexer lexer;

    if(mngr.valid()){
        switch(toValueTypeHelper(lexer.nextTokenFrom(mngr))){
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
};


CSC_END
#endif