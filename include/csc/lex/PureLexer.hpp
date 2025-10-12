#ifndef CSC_PURELEXER_HPP
#define CSC_PURELEXER_HPP

#include <map>
#include "csc/csc.hpp"
#include "csc/alias.hpp"
#include "csc/types.hpp"
#include "csc/lex/types.hpp"
#include "csc/lex/CharMngr.hpp"
#include "csc/lex/Locator.hpp"
#include "csc/lex/TokenReader.hpp"
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
    friend                    LexerAgent;
    bool                      m_autoSkipBlank;
    ReaderBranches   m_readers;
    IMapperBranches m_mappers;

    void setHint(LexResult &result) const;
    void identifierMapping(Token &token);
    void addReader(ReaderPtr reader);
    void addMapper(crString identifier, TokenType type);
    void cleanReaders();
    void cleanMappers();
};

CSC_END
#endif