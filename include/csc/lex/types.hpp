#ifndef CSC_LEX_TYPES_HPP
#define CSC_LEX_TYPES_HPP

#include "csc/csc.hpp"
#include "csc/alias.hpp"
CSC_BEGIN

enum class LexerEnvid{
    General = 0,    /* 通用解析环境，可以解析所有合法的Token */
    OnlyValue,      /* 仅可解析值，用于数组、参数等Token的解析 */
};

enum class TokenType{
    Unknown, Blank, Description,       
    Keyword, Operator, Limitor, Separator, //Limitor指数组、参数的边界符号，例如{}和()；Separator指,这类分隔符
    Integer, HexInteger, Float, String
};

enum class LexerFlag{
    OK, Finish, Wrong
};

enum class ReaderFlag{
    OK, Broken
};

struct Token{
    String         str;
    TokenType type;
};

struct CharRange{
    Char lch;
    Char rch;
};

CSC_END
#endif