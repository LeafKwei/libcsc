#ifndef CSC_CHARMNGR_HPP
#define CSC_CHARMNGR_HPP

#include "csc/csc.hpp"
#include "csc/alias.hpp"
CSC_BEGIN

class CharMngr{
public:
    enum SeekOption{Set, Cur, End};
    CharMngr(crString str, int index=0);
    
    int         index() const noexcept;
    int         length() const noexcept;
    bool      valid() const noexcept;
    Char      at(int index) const;
    Char      getch() const;
    Char      forward();
    Char      backward();
    crString str() const;
    void       seek(SeekOption option, int offset);

private:
    String m_str;
    Size_t m_index;
};

CSC_END
#endif