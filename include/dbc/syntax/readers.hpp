#ifndef DBC_SYNTAX_READERS_HPP
#define DBC_SYNTAX_READERS_HPP

#include "dbc/dbc.hpp"
#include "dbc/lex/readers.hpp"
DBC_BEGIN

class LongStringReader : public StringReader{
public:
    bool canRead(DbcChar ch) const noexcept override;
};

DBC_END
#endif