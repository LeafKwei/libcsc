#ifndef DBC_SYNTAX_FUNCTIONS_HPP
#define DBC_SYNTAX_FUNCTIONS_HPP

#include "dbc/dbc.hpp"
#include "dbc/types.hpp"
#include "dbc/lex/types.hpp"
#include "dbc/core/types.hpp"
#include "dbc/syntax/types.hpp"
#include "dbc/lex/PureLexer.hpp"
DBC_BEGIN

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
        case TokenType::Array:
            return OperandType::Value;

        default:
            return OperandType::Unexcepted;
    }
}

static inline ValueType toValueTypeHelper(const Token &token){
    //Bool
    if(token.type == TokenType::Keyword){
        if(token.buffer == "true" || token.buffer == "false"){
            return ValueType::Bool;
        }
    }

    //Integer/Double
    if(token.type == TokenType::Number){
        if(token.buffer.find('.') != Dstring::npos){
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


DBC_END
#endif