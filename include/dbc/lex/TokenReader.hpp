#ifndef DBC_TOKENREADER_HPP
#define DBC_TOKENREADER_HPP

#include "dbc/dbc.hpp"
#include "dbc/alias.hpp"
#include "dbc/lex/types.hpp"
#include "dbc/lex/structs.hpp"
DBC_BEGIN

class TokenReader{
public:
    virtual TokenType type() const noexcept =0;
    virtual bool isThisType(DbcChar ch) const noexcept =0;
    virtual void readToken(const DbcString &raw, DbcString &buffer, Locator &locator) const noexcept =0;

protected:
    virtual inline void updateLocator(DbcChar ch, Locator &locator) const noexcept{
        locator.index++;
        locator.col++;

        if(ch == '\n'){
            locator.row++;
            locator.col = 0;
    }
    }
};


DBC_END
#endif