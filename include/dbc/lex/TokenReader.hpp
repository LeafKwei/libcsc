#ifndef DBC_TOKENREADER_HPP
#define DBC_TOKENREADER_HPP

#include "dbc/dbc.hpp"
#include "dbc/alias.hpp"
#include "dbc/types.hpp"
#include "dbc/lex/types.hpp"
#include "dbc/lex/CharMngr.hpp"
DBC_BEGIN

class TokenReader{
public:
    virtual Token read(CharMngr &mngr) =0;
    virtual bool isThisType(CharMngr &mngr) =0;
    virtual TokenType type() =0;
    
protected:
    virtual bool canRead(Dchar ch) =0;
};

DBC_END
#endif