#ifndef DBC_READERS_HPP
#define DBC_READERS_HPP

#include "dbc/dbc.hpp"
#include "dbc/lex/TokenReader.hpp"
DBC_BEGIN

class BlankReader : public TokenReader{
public:
    TokenType type() const noexcept override;
    bool isThisType(DbcChar ch) const noexcept override;
    void readToken(const DbcString &raw, DbcString &buffer, Locator &locator) const noexcept override;

private:
    inline void updateLocator(DbcChar ch, Locator &locator) const noexcept;
};

DBC_END
#endif