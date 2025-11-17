#ifndef CSC_TOKENHOLDER_HPP
#define CSC_TOKENHOLDER_HPP

#include <vector>
#include <memory>
#include "csc/lex/types.hpp"
CSC_BEGIN

class TokenHolder{
public:
    using TokenList = std::vector<Token>;

public:
    void       pushToken(const Token &token);
    Token& firstToken();
    Token& tokenAt(int index);
    Size_t    size() const noexcept;
    bool      empty() const noexcept;

private:
    TokenList tokenlist_;
};

using TokenHolderPtr = std::shared_ptr<TokenHolder>;

CSC_END
#endif