#ifndef CSC_STRING_HPP
#define CSC_STRING_HPP

#include <iostream>
#include <sstream>
#include "csc/context/ScoQuerier.hpp"
CSC_BEGIN

class CscString{
public:
    CscString() =default;
    CscString(ScoQuerier querier, bool isroot);

    String localstr();                                                       /* 获取上一次生成的字符串 */
    String strfrom(ScoQuerier querier, bool isroot);     /* 以给定的walker对象开始递归生成字符串，isroot为true时不会将此walker对象的名称显示在字符串中 */

private:
    int nest_;
    std::stringstream buffer_;

    void make(ScoQuerier querier, bool isroot);
    void enterScope(const String &name);
    void leaveScope(const String &name);
    void values(const String &name, const VarQuerier &querier);
    void writeIndent();
    void writeValue(const String &value,  ValueType type);
};

CSC_END
#endif