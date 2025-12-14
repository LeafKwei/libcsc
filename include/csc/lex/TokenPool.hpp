#ifndef CSC_TOKENPOOL_HPP
#define CSC_TOKENPOOL_HPP

#include <list>
#include <set>
#include <map>
#include <memory>
#include "csc/alias.hpp"
#include "csc/lex/types.hpp"
#include "csc/lex/TokenHolder.hpp"
CSC_BEGIN

class TokenPool{
public:
    using TokenPtr = std::shared_ptr<Token>;
    using TokenList = std::list<TokenPtr>;
    using TokenTypeSet  = std::set<TokenType>;
    using TokenConvMap = std::map<String, TokenType>;

public:
    TokenPool();
    void                addToken(const Token &token);
    void                addToken(Token &&token);
    TokenHolder  nextHolder();
    bool               empty() const noexcept;
    Size_t             size() const noexcept;

private:
    TokenList           tokens_;
    TokenTypeSet   ignored_;
    TokenConvMap conv_;

    void initIgnoredToken();
    void initConvToken();
    void appendToken(const TokenPtr &ptr);
    bool isIgnoredToken(TokenType type);
    void convertTokenType(Token &token);
};

CSC_END
#endif