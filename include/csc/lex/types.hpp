#ifndef CSC_LEX_TYPES_HPP
#define CSC_LEX_TYPES_HPP

#include "csc/csc.hpp"
#include "csc/alias.hpp"
CSC_BEGIN

enum class TokenHolderType{
    OK, Ignored, Aborted
};

enum class TokenType{
    Unknown, Blank, Description, 
    Keyword, Operator,
    Integer, HexInteger, Float, String
};

struct Token{
    String         str;
    TokenType type;
};

CSC_END
#endif