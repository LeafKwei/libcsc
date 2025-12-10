#ifndef CSC_READERTREE_HPP
#define CSC_READERTREE_HPP

#include <memory>
#include "csc/alias.hpp"
#include "csc/lex/readers.hpp"
CSC_BEGIN

class ReaderTree{
public:
    using RID = int;
    using ReaderList = std::vector<TokenReader>;

private:
    RID addReader(const ReaderReadable &readable, const ReaderRead &read);
    RID addReader(const ReaderReadable &readable, const ReaderRead &read, ReaderFlag flag);
    RID addReader(const ReaderInitor &initor, const ReaderReadable &readable, 
        const ReaderRead &read, const ReaderFintor &fintor, ReaderFlag flag);

private:
    ReaderList   readers_;
};

CSC_END
#endif