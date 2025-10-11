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
    using IMapperBranches = std::map<String, TokenType>;
    using ReaderBranches = std::vector<ReaderPtr>;

public:
    PureLexer();
    LexResult nextResultFrom(CharMngr &mngr);
    void         setAutoSkipBlank(bool b);

private:
    bool                      m_autoSkipBlank;
    ReaderBranches   m_readers;
    IMapperBranches m_mappers;

    void setHint(LexResult &result) const;
    void identifierConverter(Token &token);
    void addReader(ReaderPtr ptr);
    void addIdentifierMapper(crString identifier, TokenType type);
};

CSC_END
#endif