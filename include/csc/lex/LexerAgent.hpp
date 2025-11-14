#ifndef CSC_LEXERAGENT_HPP
#define CSC_LEXERAGENT_HPP

#include "csc/lex/PureLexer.hpp"
CSC_BEGIN

class LexerAgent{
public:
    void selectEnv(PureLexer &p, LexerEnvid env)                                                  { p.selectEnv(env); }
    int    addReader(PureLexer &p, TokenReaderPtr reader)                                   { p.addReader(reader); }
    void mappingID(PureLexer &p, const String &chs, int id)                                 { p.mappingID(chs, id); }
    void addDropedType(PureLexer &p, PureLexer::InitTokenTypes types)             { p.addDropedType(types); }
    void addTypeMapper(PureLexer &p, const String &identier, TokenType type) {p.addTypeMapper(identier, type); }
};

CSC_END
#endif