#ifndef DBC_LEXHELPER_HPP
#define DBC_LEXHELPER_HPP

#include <vector>
#include <functional>
#include "dbc/dbc.hpp"
#include "dbc/alias.hpp"
#include "dbc/lex/lex.hpp"
#include "dbc/lex/structs.hpp"

DBC_BEGIN

using TokenTypeBranches = std::vector<TokenTypeBranch>;
using OptionBranches =  std::vector<OptionBranch>;

class LexHelper{
public:
    LexHelper();
    ~LexHelper();

   DbcString readToken(const DbcString &raw);
   DbcString readToken(const DbcString &raw, std::function<Option(DbcChar, TokenType, TokenType, const DbcString&)> decider);

private:
    int m_index;
    int m_rowCounter;
    int m_colCounter;
    OptionBranches m_optionBranches;
    TokenTypeBranches m_tokenTypeBranches;

    TokenType tokenTypeOf(DbcChar ch);
    void switchToHandler(Option option, DbcChar ch, DbcString &buffer, UpdatePack &pack, TokenType charType, TokenType lastCharType);
    void store(UpdatePack &pack) noexcept;
    void update(const UpdatePack &pack) noexcept;
};

DBC_END
#endif