#include "csc/lex/types.hpp"
#include "csc/utility/utility.hpp"
#include <algorithm>

CSC_BEGIN

//=================== 关键字定义 ===================
const String KW_TRUE("true");
const String KW_FALSE("false");
const String KW_ACTION("action");

//=================== 通用工具函数 ===================
String valueToString(crValue value, ValueType tp){
    std::stringstream sstream;

    switch(tp){
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

String toEscapingString(crString str){
    String tmp(str);

    auto pos = tmp.find('\"');
    while(pos != String::npos){
        tmp.insert(pos, {'\\'});          //Insert escaping symbol.
        pos = tmp.find('\"', pos+2);
    }

    return tmp;
}

CSC_END