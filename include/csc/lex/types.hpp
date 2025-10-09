#ifndef CSC_LEX_TYPES_HPP
#define CSC_LEX_TYPES_HPP

#include <cstdint>
#include <utility>
#include "csc/csc.hpp"
#include "csc/types.hpp"
CSC_BEGIN

enum class TokenTag{
    None, Float, Hex
};

enum class TokenType{
    Keyword,
    Blank, Identifier, Operator, 
    Number, String, Array
};

struct Token{
    TokenType type;
    TokenTag   tag;
    String         str;
};

enum class LexOption{
    Aborted, Ignored, Unknown     //Aborted：已无可读取的token，Ignored：该token需要忽略，Unknown：未知的token
};

using LexResult = std::pair<LexOption, Token>;

CSC_END
#endif