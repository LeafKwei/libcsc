#ifndef CSC_PURELEXER_HPP
#define CSC_PURELEXER_HPP

#include <map>
#include <vector>
#include "csc/lex/CharMngr.hpp"
#include "csc/lex/TokenPool.hpp"
#include "csc/lex/TokenReader.hpp"
CSC_BEGIN

enum class LxErrno{
    OK, Bad, Done
};

class PureLexer{
public:
    using ReaderList      = std::vector<TokenReader>;
    using CharMapping = std::map<Char, std::vector<int>>;

public:
    PureLexer();
    LxErrno readToken(CharMngr &mngr, TokenPool &pool);

private:
    ReaderList         readers_;
    CharMapping    chmapping_;

    void installReaders();
    int    findReader(CharMngr &mngr);
    void addCharMapping(Char ch, int id);
    void addCharMapping(const String &chs, int id);
    int    addReader(ReaderReadable readable, ReaderRead read);
    int    addReader(ReaderReadable readable, ReaderRead read, ReaderFlag flag);
    int    addReader(ReaderInitor initor, ReaderReadable readable, ReaderRead read);
    int    addReader(ReaderInitor initor, ReaderReadable readable, ReaderRead read, ReaderFlag flag);
    int    addReader(ReaderInitor initor, ReaderReadable readable, ReaderRead read, ReaderFintor fintor, ReaderFlag flag);
};

CSC_END

#endif