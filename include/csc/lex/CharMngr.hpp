#ifndef CSC_CHARMNGR_HPP
#define CSC_CHARMNGR_HPP

#include "csc/csc.hpp"
#include "csc/alias.hpp"
CSC_BEGIN

class CharMngr{
public:
    enum SeekOption{Set, Cur, End};
    CharMngr(const String &str, Index_t index=0);
    
    Index_t  index() const noexcept;
    Size_t    length() const noexcept;
    Size_t    surplus() const noexcept;            //获取从index位置到字符串末尾剩余的字符数
    bool      valid() const noexcept;
    Char      at(Index_t index) const;
    Char      near(Offset_t offset) const;          //获取index附近的字符，例如near(1)可获取index+1处的字符
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