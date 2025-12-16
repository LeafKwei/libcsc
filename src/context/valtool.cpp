#include <cstdlib>
#include "csc/context/valtool.hpp"
CSC_BEGIN

ValueType valueTypeof(const Token &token){
    switch(token.type){
        case TokenType::Keyword:
            if(token.str == "true" || token.str == "false") return ValueType::Bool;
            return ValueType::Unknown;
        case TokenType::Integer:
            return ValueType::Integer;
        case TokenType::Float:
            return ValueType::Double;
        case TokenType::String:
            return ValueType::String;
        default:
            return ValueType::Unknown;
    }
}

Value makeValueFrom(const Token &token, ValueType type){
    switch(type){
        case ValueType::Bool:
            return (token.str == "true") ? true : false;
        case ValueType::Integer:
            if(token.type == TokenType::HexInteger) return strtol(token.str.c_str(), NULL, 16);
            return strtol(token.str.c_str(), NULL, 10);
        case ValueType::Double:
            return strtod(token.str.c_str(), NULL);
        case ValueType::String:
            return token.str;
        default:
            return makeZeroValue(type);
    }
}

Value makeZeroValue(ValueType type){
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

CSC_END