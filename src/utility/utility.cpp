#include "csc/lex/types.hpp"
#include "csc/utility/utility.hpp"
#include <algorithm>

CSC_BEGIN

////////////////////////////////////////////////////////////////////////////////////////关键字
const String KW_TRUE("true");
const String KW_FALSE("false");
const String KW_ACTION("action");
const String KW_VOID("void");
const String KW_ENTER("enter");

////////////////////////////////////////////////////////////////////////////////////////通用工具函数
/* 如果字符串的内容包含引号，那么在每个引号前添加一个转义字符，返回转换后的字符串 */
String toEscapingString(const String &str){
    String tmp(str);

    auto pos = tmp.find('\"');
    while(pos != String::npos){
        tmp.insert(pos, {'\\'});          //Insert escaping symbol.
        pos = tmp.find('\"', pos+2);
    }

    return tmp;
}

/* 计算从字符串开头到指定的offset位置之间的行数和列数 */
Rowcol locateFrom(const String &str, Offset_t offset){
    Rowcol rc{0, 0};

    Offset_t size = str.size();
    auto endidx = (size > offset) ? offset : size;
    for(Offset_t idx = 0; idx < endidx; idx++){
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