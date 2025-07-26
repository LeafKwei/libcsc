#ifndef DBC_CHARMNGR_HPP
#define DBC_CHARMNGR_HPP

#include "dbc/lex/CharPicker.hpp"
DBC_BEGIN

class CharMngr : CharPicker{
public:
    CharMngr(const Dstring &raw);

private:
    Dstring m_raw;
};


DBC_END
#endif