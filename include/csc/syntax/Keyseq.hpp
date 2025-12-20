#ifndef CSC_KEYSEQ_HPP
#define CSC_KEYSEQ_HPP

#include "csc/alias.hpp"
#include "csc/syntax/types.hpp"
CSC_BEGIN

class Keyseq{
public:
    Keyseq& start(const String &str);
    Keyseq& append(const String &str);
    Keyseq& clear();
    bool        empty() const noexcept;
    const String& seq() const noexcept;
    
private:
    String seq_;
};

CSC_END
#endif