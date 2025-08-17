#ifndef DBC_PURE_LEXER_HPP
#define DBC_PURE_LEXER_HPP

#include <map>
#include "dbc/dbc.hpp"
#include "dbc/alias.hpp"
#include "dbc/types.hpp"
#include "dbc/lex/types.hpp"
#include "dbc/lex/CharMngr.hpp"
#include "dbc/lex/Locator.hpp"
#include "dbc/lex/TokenReader.hpp"
#include "dbc/lex/PureLexer.hpp"
DBC_BEGIN

class  PureLexer{
public:
    PureLexer();
    Token nextTokenFrom(CharMngr &mngr);
    void setAutoSkipBlank(bool b);

private:
    bool m_autoSkipBlank;
    ReaderBranches m_readers;

    inline bool isIgnoredToken(TokenType type) const noexcept;
    Token& tokenConvert(Token &token);
    void installReaders();
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

DBC_END
#endif