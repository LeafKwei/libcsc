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
    LexResult nextResultFrom(CharMngr &mngr);
    void         setAutoSkipBlank(bool b);

private:
    bool m_autoSkipBlank;
    ReaderBranches m_readers;
    ConverterBranches m_converters;

    void setHint(LexResult &result) const;
    void identifierConverter(Token &token);
    void installReaders();
    void installConverters();
};

CSC_END
#endif