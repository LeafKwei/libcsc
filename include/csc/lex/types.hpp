#ifndef CSC_LEX_TYPES_HPP
#define CSC_LEX_TYPES_HPP

#include "csc/csc.hpp"
#include "csc/alias.hpp"
CSC_BEGIN

enum class TokenType{
    Unknown, Blank, Description, Identifer,
    Keyword, Operator, Limitor, Separator, //Limitor指数组、参数的边界符号，例如{}和()；Separator指,这类分隔符
    Integer, HexInteger, Float, String
};

struct Token{
    String         str;
    TokenType type;
    Offset_t      offset;
};

CSC_END
#endif