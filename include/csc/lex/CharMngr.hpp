#ifndef CSC_CHARMNGR_HPP
#define CSC_CHARMNGR_HPP

#include "csc/csc.hpp"
#include "csc/alias.hpp"
CSC_BEGIN

class CharMngr{
public:
    enum SeekOption{Set, Cur, End};
    CharMngr(const String &str, int index=0);
    
    int         index() const noexcept;
    int         length() const noexcept;
    bool      valid() const noexcept;
    Char      at(int index) const;
    Char      getch() const;
    Char      forward();
    Char      backward();
    void       seek(SeekOption option, int offset);
    const String &str() const;

private:
    String m_str;
    Size_t m_index;
};

CSC_END
#endif