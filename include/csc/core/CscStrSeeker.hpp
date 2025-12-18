#ifndef CSC_STRSEEKER_HPP
#define CSC_STRSEEKER_HPP

#include <iostream>
#include <sstream>
#include "csc/context/ContextSeeker.hpp"
CSC_BEGIN

/* CscStrSeeker是对ContextSeeker的实现，它主要提供给CscHandler::toString函数使用，可以按照csc配置文件规则将Context内部的内容转换为csc格式的字符串 */
class CscStrSeeker : public ContextSeeker{
public:
    CscStrSeeker();
    void enterScope(UID id, const String &name) override;
    void leaveScope(UID id, const String &name) override;
    void values(const String &name, const Querier &querier) override;
    String toString();

private:
    int nest_;
    std::stringstream buffer_;

    void writeIndent();
    void writeValue(const String &value,  ValueType type);
    ValueType arrayToValue(ValueType type);
};

CSC_END
#endif