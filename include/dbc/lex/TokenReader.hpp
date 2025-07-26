#ifndef DBC_TOKENREADER_HPP
#define DBC_TOKENREADER_HPP

#include "dbc/dbc.hpp"
#include "dbc/alias.hpp"
#include "dbc/types.hpp"
#include "dbc/lex/structs.hpp"
#include "dbc/lex/CharPicker.hpp"
DBC_BEGIN

class TokenReader{
public:
    virtual Token readToken(CharPicker &picker) const noexcept =0;       //Read matched character. No token was read if token.type == Unknown
};


DBC_END
#endif