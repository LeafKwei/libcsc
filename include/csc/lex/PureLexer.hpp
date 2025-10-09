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

class  PureLexer{
public:
    using ConverterBranches = std::map<String, TokenType>;
    using ReaderPtr = std::shared_ptr<TokenReader>;
    using ReaderBranches = std::vector<ReaderPtr>;

public:
    PureLexer();
    LexResult nextTokenFrom(CharMngr &mngr);
    void         setAutoSkipBlank(bool b);

private:
    bool m_autoSkipBlank;
    ReaderBranches m_readers;
    ConverterBranches m_converters;

    inline bool isIgnoredToken(const LexResult &res) const noexcept;
    Token&     identifierConverter(Token &token);
    void           installReaders();
    void           installConverters();
};

inline bool PureLexer::isIgnoredToken(const LexResult &res) const noexcept{
    return (res.first == LexOption::Ignored || (res.second.type == TokenType::Blank && m_autoSkipBlank));
}

CSC_END
#endif