#ifndef CSC_PURELEXERAGENT_HPP
#define CSC_PURELEXERAGENT_HPP

#include "csc/lex/PureLexer.hpp"
CSC_BEGIN

class PureLexerAgent{
public:
    int    addReader(PureLexer &p, TokenReaderPtr reader)                          { p.addReader(reader); }
    void mappingReader(PureLexer &p, const String &chs, int id)                { p.mappingReader(chs, id); }
    void mappingReader(PureLexer &p, const CharRange &range, int id)    { p.mappingReader(range, id); }
    void addDropedType(PureLexer &p, PureLexer::InitTokenTypes types)   { p.addDropedType(types); }
};

CSC_END
#endif