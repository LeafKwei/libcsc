#ifndef CSC_LEX_TYPES_HPP
#define CSC_LEX_TYPES_HPP

#include "csc/csc.hpp"
#include "csc/alias.hpp"
CSC_BEGIN

enum class LexerState{
    OK,      //读取成功
    Finish, //无更多可读取内容
    Unexcepted, //出现不可识别的字符
};

enum class LexerCond{
    Done,        //单个token读取完毕
    Begin,        //开始一组连续的token的读取
    End           //结束读取
};

enum class TokenType{
    Unknown, Blank, Description,       
    Keyword, Operator, Limitor, Separator, //Limitor指数组、参数的边界符号，例如{}和()；Separator指,这类分隔符
    Integer, HexInteger, Float, String,
};

struct Token{
    String         str;
    TokenType type;
};

struct CharRange{
    Char lch;
    Char rch;
};

class PureLexerAgent;

CSC_END
#endif