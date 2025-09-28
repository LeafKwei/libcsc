#include "csc/lex/types.hpp"
#include "csc/utility/utility.hpp"
#include <algorithm>

CSC_BEGIN

//=================== 关键字定义 ===================
const String KW_TRUE("true");
const String KW_FALSE("false");
const String KW_ACTION("action");

//=================== 通用工具函数 ===================
String join(String splitor, const std::vector<String> &elements, const std::initializer_list<String> &filters){
    String result;

    for(Size_t idx = 0; idx < elements.size(); idx++){
        auto &e = elements.at(idx);
        result = result + e;
        if(idx + 1 >= elements.size()) continue;                                             //Don't put splitor if 'e' is last element.
        if(std::find(filters.begin(), filters.end(), e) != filters.end()) continue;   //Don't put splitor if 'e' is in filter.
        result = result + splitor;
    }

    return result;
}

int baseOf(crString str){
    if(str.substr(0, 2) == "0x") return 16;
    return 10;
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