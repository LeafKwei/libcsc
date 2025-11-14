#ifndef CSC_LEXERAGENT_HPP
#define CSC_LEXERAGENT_HPP

#include "csc/lex/PureLexer.hpp"
CSC_BEGIN

class LexerAgent{
public:
    void selectEnv(PureLexer &p, LexerEnvid env)                                          { p.selectEnv(env); }
    int    addReader(PureLexer &p, TokenReaderPtr reader)                          { p.addReader(reader); }
    void mappingReader(PureLexer &p, const String &chs, int id)                { p.mappingReader(chs, id); }
    void mappingReader(PureLexer &p, const CharRange &range, int id)    { p.mappingReader(range, id); }
    void addDropedType(PureLexer &p, PureLexer::InitTokenTypes types)   { p.addDropedType(types); }
};

CSC_END
#endif