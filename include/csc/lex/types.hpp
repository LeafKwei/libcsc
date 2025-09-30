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
    Number, NumberF, NumberH,  //Number标准整型数字，例如114；NumberF浮点型数字，例如51.4；NumberH十六进制型数字，例如0xFF
    String, 
    Array
};

struct Token{
    TokenType type;
    String buffer;
};

CSC_END
#endif