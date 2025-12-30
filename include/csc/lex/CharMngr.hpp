#ifndef CSC_CHARMNGR_HPP
#define CSC_CHARMNGR_HPP

#include "csc/csc.hpp"
#include "csc/alias.hpp"
CSC_BEGIN

class CharMngr{
public:
    enum SeekOption{Set, Cur, End};
    CharMngr(const String &str, int index=0);
    
    Index_t  index() const noexcept;
    Size_t    length() const noexcept;
    Size_t    surplus() const noexcept;
    bool      valid() const noexcept;
    Char      at(int index) const;
    Char      near(int offset) const;          //获取index附近的Char
    Char      getch() const;
    Char      forward();
    Char      backward();
    void       seek(SeekOption option, int offset);
    const String &str() const;

private:
    String  str_;
    Index_t index_;
};

CSC_END
#endif