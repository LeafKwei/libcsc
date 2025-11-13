#ifndef CSC_LEX_TYPES_HPP
#define CSC_LEX_TYPES_HPP

#include "csc/csc.hpp"
#include "csc/alias.hpp"
CSC_BEGIN

enum class LexerFlag{
    Begin,        //开始一组连续的token的读取
    End           //结束读取
};

enum class TokenHolderType{
    OK, Ignored, Aborted
};

enum class TokenType{
    Unknown, Blank, Description, Bound,       //Bound指数组、参数的边界符号，例如{}和()
    Keyword, Operator,
    Integer, HexInteger, Float, String,
    Array, Argument
};

struct Token{
    String         str;
    TokenType type;
};

/* 用于表达式“lch <= ch <= rch”的结构体，PureLexer将会判断ch是否处于lch和rch的区间内，并以此选择对应的TokenReader */
struct CharRange{
    Char lch;
    Char rch;
};

class PureLexerAgent;

CSC_END
#endif