#include <cstdlib>
#include <iostream>
#include <sstream>
#include "csc/context/val.hpp"
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

String valueToString(const Value &value, ValueType type){
    std::stringstream sstream;

    switch(type){
        case ValueType::Bool:
            sstream << (std::any_cast<CppType<ValueType::Bool>::type>(value) ? "true" : "false");
            break;
        case ValueType::Integer:
            sstream << std::any_cast<CppType<ValueType::Integer>::type>(value);
            break;
        case ValueType::Double:
            sstream << std::any_cast<CppType<ValueType::Double>::type>(value);
            break;
        case ValueType::String:
            return std::any_cast<CppType<ValueType::String>::type>(value);
            break;
        default:
            return "";
    }

    return sstream.str();
}

CSC_END