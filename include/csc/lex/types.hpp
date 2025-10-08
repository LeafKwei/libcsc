#ifndef CSC_LEX_TYPES_HPP
#define CSC_LEX_TYPES_HPP

#include <cstdint>
#include "csc/csc.hpp"
#include "csc/types.hpp"
CSC_BEGIN

enum class TokenTag{
    None, Float, Hex
};

enum class TokenType{
    Aborted, Ignored, Unknown, 
    Keyword,
    Blank, Identifier, Operator, 
    Number, String, Array
};

struct Token{
    TokenType type;
    TokenTag   tag;
    String         str;
};

CSC_END
#endif