#ifndef DBC_CHARMNGR_HPP
#define DBC_CHARMNGR_HPP

#include "dbc/dbc.hpp"
#include "dbc/alias.hpp"
DBC_BEGIN

class CharMngr{
public:
    enum SeekOption{Set, Current, End};
    CharMngr(const Dstring &str, int index=0);
    
    int index() const;
    int length() const;
    bool valid() const;
    Dchar at(int index) const;
    Dchar forward();
    Dchar backward();
    const Dstring& str() const;
    void seek(SeekOption option, int offset);

private:
    int m_index;
    Dstring m_str;
};

DBC_END
#endif