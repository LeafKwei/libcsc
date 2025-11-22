#ifndef CSC_PURELEXER_HPP
#define CSC_PURELEXER_HPP

#include <vector>
#include "csc/lex/readers.hpp"
CSC_BEGIN

class PureLexer{
public:
    using RID = int;
    using ReaderList = std::vector<TokenReader>;

public:
    RID addReader(const ReaderReadable &readable, const ReaderRead &read);
    RID addReader(const ReaderReadable &readable, const ReaderRead &read, ReaderFlag flag);
    RID addReader(const ReaderInitor &initor, const ReaderReadable &readable, 
        const ReaderRead &read, const ReaderFintor &fintor, ReaderFlag flag);

private:
    ReaderList   readers_;
};

CSC_END

#endif