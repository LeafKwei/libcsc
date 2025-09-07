#ifndef CSC_CHARMNGR_HPP
#define CSC_CHARMNGR_HPP

#include "csc/csc.hpp"
#include "csc/alias.hpp"
CSC_BEGIN

class CharMngr{
public:
    enum SeekOption{Set, Cur, End};
    CharMngr(const CscStr &str, int index=0);
    
    int         index() const;
    int         length() const;
    bool      valid() const;
    CscChar at(int index) const;
    CscChar getch() const;
    CscChar forward();
    CscChar backward();
    const CscStr& str() const;
    void       seek(SeekOption option, int offset);

private:
    int m_index;
    CscStr m_str;
};

CSC_END
#endif