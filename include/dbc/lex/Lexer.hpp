#ifndef DBC_LEXCER_HPP
#define DBC_LEXCER_HPP

#include <map>
#include "dbc/dbc.hpp"
#include "dbc/alias.hpp"
#include "dbc/types.hpp"
#include "dbc/lex/types.hpp"
#include "dbc/lex/CharMngr.hpp"
#include "dbc/lex/Locator.hpp"
#include "dbc/lex/TokenReader.hpp"
DBC_BEGIN

using ConverterBranches = std::map<Dstring, TokenType>;

class Lexer{
public:
    Lexer(const Dstring &str);
    Token nextToken();
    Locator locator() const;
    bool valid() const;
    const Dstring& str() const;
    void setAutoSkipBlank(bool b);

private:
    CharMngr m_mngr;
    bool m_autoSkipBlank;
    ReaderBranches m_readers;
    ConverterBranches m_converters;

    inline bool isIgnoredToken(TokenType type) const noexcept;
    Token& identifierConverter(Token &token);
    void installReaders();
    void installConverters();
};

inline bool Lexer::isIgnoredToken(TokenType type) const noexcept{
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