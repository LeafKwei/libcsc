#ifndef DBC_TOKENREADER_HPP
#define DBC_TOKENREADER_HPP

#include "dbc/dbc.hpp"
#include "dbc/alias.hpp"
#include "dbc/types.hpp"
#include "dbc/lex/structs.hpp"
DBC_BEGIN

class TokenReader{
public:
    virtual TokenType type() const noexcept =0;                    //Get TokenType of this reader
    virtual bool isThisType(DbcChar ch) const noexcept =0; //Check whether ch matches this reader. Use this one when match reader
    virtual bool canRead(DbcChar ch) const noexcept =0;    //Check whether ch can be read by this reader. Use this one when read character
    virtual void readToken(const DbcString &raw, DbcString &buffer, Locator &locator) const noexcept =0; //Read matched character

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