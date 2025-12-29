#ifndef CSC_TOKENHOLDER_HPP
#define CSC_TOKENHOLDER_HPP

#include <vector>
#include <memory>
#include "csc/lex/types.hpp"
CSC_BEGIN

class TokenPool;
class TokenHolder{
public:
    using TokenPtr = std::shared_ptr<Token>;
    using TokenList = std::vector<TokenPtr>;

public:
    Token& token();
    Token& tokenAt(int index);
    bool      plural() const noexcept;
    bool      empty() const noexcept;
    Size_t    size() const noexcept;

private:
    friend      TokenPool;
    bool         plural_;
    TokenList tokens_;

    void addToken(const TokenPtr &token);
    void setPlural(bool plural);
};

CSC_END
#endif