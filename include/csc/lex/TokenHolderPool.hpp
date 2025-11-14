#ifndef CSC_TOKENHOLDERPOOL_HPP
#define CSC_TOKENHOLDERPOOL_HPP

#include <vector>
#include "csc/lex/TokenHolder.hpp"
CSC_BEGIN

class TokenHolderPool{
public:
    using HolderPtr  = TokenHolderPtr;
    using HolderList = std::vector<HolderPtr>;
    
public:
    
    TokenHolder& useLastHolder();               //返回holderlist末尾的TokenHolder的引用
    HolderPtr         takeFirstHolder();            //获取holderlist中首个TokenHolder的指针，相应的，该指针将从holderlist中删除
    Size_t               size() const noexcept;      //获取holderlist中的TokenHolder的数量
    bool                 empty() const noexcept;  //返回holderlist是否为空
    void                 clear();                               //清空holderlist内的所有TokenHolder
    
private:
    HolderList holderlist_;
};

CSC_END
#endif