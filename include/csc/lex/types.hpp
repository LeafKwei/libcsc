#ifndef CSC_LEX_TYPES_HPP
#define CSC_LEX_TYPES_HPP

#include <cstdint>
#include "csc/csc.hpp"
#include "csc/types.hpp"
CSC_BEGIN

enum class TokenType{
    Aborted, Ignored, Unexcepted, 
    Keyword,
    Blank, Identifier, Operator, 
    Number, String, Array
};

struct Token{
    TokenType type;
    CscStr buffer;
};

CSC_END
#endif