#ifndef CSC_LEXERAGENT_HPP
#define CSC_LEXERAGENT_HPP

#include "csc/lex/PureLexer.hpp"
CSC_BEGIN

class LexerAgent{
public:
    void selectEnv(PureLexer &p, LexerLevel level)                                                    { p.selectLevel(level); }
    int    addReader(PureLexer &p, TokenReaderPtr reader)                                     { p.addReader(reader); }
    void addIDMapping(PureLexer &p, const String &chs, int id)                             { p.addIDMapping(chs, id); }
    void addDropedType(PureLexer &p, PureLexer::InitTokenTypes types)               { p.addDropedType(types); }
    void addIdentMapping(PureLexer &p, const String &identier, TokenType type) {p.addIdentMapping(identier, type); }
    void addGuideMapping(PureLexer &p, Char ch, LexerGuide guide)                    { p.addGuideMapping(ch, guide);}
};

CSC_END
#endif