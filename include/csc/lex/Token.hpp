#ifndef CSC_TOKEN_HPP
#define CSC_TOKEN_HPP

#include <vector>
#include "csc/lex/types.hpp"
CSC_BEGIN

class Tokener{
public:
    int                 expand();                       //新增一个Token对象到strlist_末尾
    Token&         token();                         //获取strlist_中的首个Token对象
    Token&         tokenAt(int index);        //获取strlist_中指定位置的String对象
    Size_t            size() const noexcept;  //获取strlist_中的Token对象数量
    TokenerState stateofTokener();         //获取TokenerState
    TokenerType typeofTokener();          //获取ToknerType

private:
    TokenerType                    type_;
    TokenerState                   state_;
    std::vector<Token>         strlist_;
};

CSC_END
#endif