#ifndef CSC_TOKENPOOL_HPP
#define CSC_TOKENPOOL_HPP

#include <list>
#include "csc/lex/types.hpp"
#include "csc/lex/TokenHolder.hpp"
CSC_BEGIN

class TokenPool{
public:
    using HolderPtr = TokenHolderPtr;
    using HolderList = std::list<TokenHolderPtr>;

public:
    TokenHolder& makeHolder();       /* 创建一个TokenHolder的堆对象并赋值给holderptr，返回其引用 */
    TokenHolder& referHolder();        /* 返回holderptr保存的TokenHolder对象的引用 */
    HolderPtr         takeFirstHolder(); /* 返回首个TokenHolder的指针，并清除holderlist中对应的指针 */
    void                  saveHolder();       /* 将holderptr添加到holderlist中 */
    bool                 empty() const noexcept;  /* 返回holderlist是否为空 */

private:
    HolderPtr   holderptr_;
    HolderList  holderlist_;   
};

CSC_END
#endif