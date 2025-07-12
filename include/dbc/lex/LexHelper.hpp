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
DBC_BEGIN

using TokenReaderPtr = std::shared_ptr<TokenReader>;
using ReaderBranches = std::vector<TokenReaderPtr>;

class LexHelper{
public:
    LexHelper();
    ~LexHelper();

    bool hasMore(const DbcString &raw) const noexcept;
    Token readToken(const DbcString &raw);                                                //Read token by reader which is automatically selected by 'raw.at[index]'
    Token readToken(const DbcString &raw, TokenType type);                     //Read token by reader of specific type
    Token readToken(const DbcString &raw, const TokenReader &reader); //Rread token by specific reader
    int numberOfRow() const noexcept;
    int numberOfCol() const noexcept;
    int numberOfLocation()const noexcept;
    const Locator& locator() const noexcept;
    void setLocator(const Locator &locator) noexcept;
    void resetLocator() noexcept;

private:
    Locator m_locator;
    ReaderBranches m_readerBranches;

    void installReaders();
};


DBC_END
#endif