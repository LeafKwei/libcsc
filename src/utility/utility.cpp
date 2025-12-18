#include "csc/lex/types.hpp"
#include "csc/utility/utility.hpp"
#include <algorithm>

CSC_BEGIN

//=================== 关键字定义 ===================
const String KW_TRUE("true");
const String KW_FALSE("false");
const String KW_ACTION("action");

//=================== 通用工具函数 ===================

String toEscapingString(const String &str){
    String tmp(str);

    auto pos = tmp.find('\"');
    while(pos != String::npos){
        tmp.insert(pos, {'\\'});          //Insert escaping symbol.
        pos = tmp.find('\"', pos+2);
    }

    return tmp;
}

CSC_END