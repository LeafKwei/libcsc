#ifndef DBC_LEXHELPER_HPP
#define DBC_LEXHELPER_HPP

#include <vector>
#include <stack>
#include <memory>
#include "dbc/dbc.hpp"
#include "dbc/alias.hpp"
#include "dbc/types.hpp"
#include "dbc/lex/structs.hpp"
#include "dbc/lex/readers.hpp"
#include "dbc/lex/CharReceiver.hpp"
DBC_BEGIN

using TokenReaderPtr = std::shared_ptr<TokenReader>;
using ReaderBranches = std::vector<TokenReaderPtr>;

class LexHelper{
public:
    LexHelper(const Dstring &raw);
    ~LexHelper();

    bool hasMore(const Dstring &raw) const noexcept;
    Token readToken(const Dstring &raw);                                                //Read token by reader which is automatically selected by 'raw.at[index]'
    Token readToken(const Dstring &raw, TokenType type);                     //Read token by reader of specific type
    int numberOfRow() const noexcept;
    int numberOfCol() const noexcept;

private:
    
    ReaderBranches m_readerBranches;

    void installReaders();
};


DBC_END
#endif