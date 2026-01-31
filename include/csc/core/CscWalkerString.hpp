#ifndef CSC_WALKERSTRING_HPP
#define CSC_WALKERSTRING_HPP

#include <iostream>
#include <sstream>
#include "csc/context/Walker.hpp"
CSC_BEGIN

class CscWalkerString{
public:
    CscWalkerString() =default;
    CscWalkerString(Walker walker, bool isroot);

    String localstr();                                               /* 获取上一次生成的字符串 */
    String strfrom(Walker walker, bool isroot);     /* 以给定的walker对象开始递归生成字符串，isroot为true时不会将此walker对象的名称显示在字符串中 */

private:
    int nest_;
    std::stringstream buffer_;

    void make(Walker walker, bool isroot);
    void enterScope(const String &name);
    void leaveScope(const String &name);
    void values(const String &name, const Querier &querier);
    void writeIndent();
    void writeValue(const String &value,  ValueType type);
};

CSC_END
#endif