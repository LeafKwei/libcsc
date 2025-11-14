#ifndef CSC_TOKENHOLDER_HPP
#define CSC_TOKENHOLDER_HPP

#include <vector>
#include <memory>
#include "csc/lex/types.hpp"
CSC_BEGIN

class TokenHolder{
public:
    using TokenList  = std::vector<Token>;

public:
    Token&         tokenAt(int index);           /* 获取tokenlist中指定位置的Token对象 */
    Size_t            size() const noexcept;      /* 获取tokenlist中的Token对象数量 */

private:
    TokenList      tokenlist_;
};

using TokenHolderPtr = std::shared_ptr<TokenHolder>;

CSC_END
#endif