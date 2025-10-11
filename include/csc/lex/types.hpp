#ifndef CSC_LEX_TYPES_HPP
#define CSC_LEX_TYPES_HPP

#include <cstdint>
#include <utility>
#include <functional>
#include "csc/csc.hpp"
#include "csc/types.hpp"
CSC_BEGIN

enum class TokenTag{
    None, Float, Hex
};

enum class TokenType{
    Unknown, Description,
    Keyword,
    Blank, Identifier, Operator, 
    Number, String, Array
};

/**
 * LexHint决定了上层功能对token的取舍，OK表示该token可以正常使用，Ignored表示该token应该被忽略，
 * Aborted表示已没有可以读取的token
 */
enum class LexHint{
    OK, Ignored,
    Aborted
};

struct Token{
    TokenType type;
    TokenTag   tag;
    String         str;
};

struct LexResult{
    LexHint hint;
    Token    token;
};

CSC_END
#endif