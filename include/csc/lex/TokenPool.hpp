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

class PureLexer;
class TokenPool{
public:
    using TokenPtr = std::shared_ptr<Token>;
    using TokenList = std::list<TokenPtr>;
    using TokenTypeSet  = std::set<TokenType>;
    using TokenConvMap = std::map<String, TokenType>;
    using PluralTokenRule = std::vector<std::pair<String, String>>;

public:
    TokenPool();
    TokenHolder  nextHolder();
    bool               empty() const noexcept;
    Size_t             size() const noexcept;

private:
    friend               PureLexer;          //addToken函数只提供给PureLexer使用，因此将PureLexer声明为友元，既能让PureLexer访问到addToken函数，又不会增加对外暴露的public函数的数量
    TokenList          tokens_;
    TokenTypeSet   ignored_;
    TokenConvMap conv_;
    PluralTokenRule rule_;

    void addToken(const Token &token);
    void addToken(Token &&token);
    void initIgnoredToken();
    void initConvToken();
    void initPluralRule();
    void appendToken(const TokenPtr &ptr);
    bool isIgnoredToken(TokenType type);
    void convertTokenType(Token &token);
    bool isPluralTokenBegin(const String &str);
    bool isPluralTokenEnd(const String &str);
    void fillHolderAsPlural(TokenHolder &holder);
    void fillHolderAsNonPlural(TokenHolder &holder);
};

CSC_END
#endif