#include "dbc/syntax/readers.hpp"
DBC_BEGIN

//=================== StringReader ===================
bool LongStringReader::canRead(Dchar ch) const noexcept{
    if(ch == '\"') return false;
    return true;
}

DBC_END