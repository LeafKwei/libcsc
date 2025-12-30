#include "csc/lex/types.hpp"
#include "csc/utility/utility.hpp"
#include <algorithm>

CSC_BEGIN

////////////////////////////////////////////////////////////////////////////////////////关键字
const String KW_TRUE("true");
const String KW_FALSE("false");
const String KW_ACTION("action");
const String KW_VOID("void");

////////////////////////////////////////////////////////////////////////////////////////通用工具函数
String toEscapingString(const String &str){
    String tmp(str);

    auto pos = tmp.find('\"');
    while(pos != String::npos){
        tmp.insert(pos, {'\\'});          //Insert escaping symbol.
        pos = tmp.find('\"', pos+2);
    }

    return tmp;
}

Rowcol locateFrom(const String &str, Offset_t offset){
    Rowcol rc{0, 0};

    auto endidx = (str.size() > offset) ? offset : str.size();
    for(Size_t idx = 0; idx < endidx; idx++){
        if(str.at(idx) == '\n'){
            ++rc.first;
            rc.second = 0;
            continue;
        }

        ++rc.second;
    }

    return rc;
}

CSC_END