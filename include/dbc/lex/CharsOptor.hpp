#ifndef DBC_CHARSOPTOR_HPP
#define DBC_CHARSOPTOR_HPP

#include "dbc/dbc.hpp"
#include "dbc/alias.hpp"
DBC_BEGIN

class CharsOptor{
public:
    CharsOptor(const Dstring &raw);
    CharsOptor(const Dstring &raw, int index);
    CharsOptor(const CharsOptor &oth);
    CharsOptor& operator=(const CharsOptor &oth) =delete;

    bool startWith(const Dstring &dstr) const noexcept;

private:
    int m_index;
    const Dstring &m_raw;
};

DBC_END
#endif