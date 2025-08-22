#ifndef CSC_PURE_LEXER_HPP
#define CSC_PURE_LEXER_HPP

#include <map>
#include "csc/csc.hpp"
#include "csc/alias.hpp"
#include "csc/types.hpp"
#include "csc/lex/types.hpp"
#include "csc/lex/CharMngr.hpp"
#include "csc/lex/Locator.hpp"
#include "csc/lex/TokenReader.hpp"
#include "csc/lex/PureLexer.hpp"
CSC_BEGIN

using ConverterBranches = std::map<CscStr, TokenType>;

class  PureLexer{
public:
    PureLexer();
    Token nextTokenFrom(CharMngr &mngr);
    void setAutoSkipBlank(bool b);

private:
    bool m_autoSkipBlank;
    ReaderBranches m_readers;
    ConverterBranches m_converters;

    inline bool isIgnoredToken(TokenType type) const noexcept;
    Token& identifierConverter(Token &token);
    void installReaders();
    void installConverters();
};

inline bool PureLexer::isIgnoredToken(TokenType type) const noexcept{
    switch(type){
        case TokenType::Ignored:
            return true;
        case TokenType::Blank:
            return m_autoSkipBlank;
        default:
            return false;
    }
}

CSC_END
#endif