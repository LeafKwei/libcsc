#ifndef CSC_LEXERAGENT_HPP
#define CSC_LEXERAGENT_HPP

#include "csc/lex/types.hpp"
#include "csc/lex/TokenReader.hpp"
#include "csc/lex/PureLexer.hpp"
CSC_BEGIN

/**
 * LexerAgent用以向xxxlexer_initializer类提供访问PureLexer类的私有函数的功能(通过PureLexer将LexerAgent声明为友元来实现)，
 * 如此，PureLexer就可以在不提供多余public函数的情况下向外部函数暴露自己的内部功能。
 */
class LexerAgent{
public:
    void addReader(PureLexer &lexer, ReaderPtr reader)                               { lexer.addReader(reader); }
    void addMapper(PureLexer &lexer, crString identifier, TokenType type)  { lexer.addMapper(identifier, type); }
    void cleanReaders(PureLexer &lexer)                                                        { lexer.cleanReaders(); }
    void cleanMappers(PureLexer &lexer)                                                       { lexer.cleanMappers(); }
};

CSC_END
#endif