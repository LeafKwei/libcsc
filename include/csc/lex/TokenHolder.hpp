#ifndef CSC_TOKENHOLDER_HPP
#define CSC_TOKENHOLDER_HPP

#include <vector>
#include <memory>
#include "csc/lex/types.hpp"
CSC_BEGIN

class TokenHolder{
public:
    using Type         = TokenHolderType;
    using TokenList  = std::vector<Token>;

public:
    TokenHolder();
    Token&         newToken();                      //新增一个Token对象到tokenlist_末尾，并返回其引用
    Token&         firstToken();                       //获取tokenlist中的首个Token对象
    Token&         tokenAt(int index);           //获取tokenlist中指定位置的Token对象
    Size_t            size() const noexcept;      //获取tokenlist中的Token对象数量
    Type              type() const noexcept;    //获取TokenHolder的类型

private:
    Type              type_;
    TokenList      tokenlist_;
};

using TokenHolderPtr = std::shared_ptr<TokenHolder>;

CSC_END
#endif