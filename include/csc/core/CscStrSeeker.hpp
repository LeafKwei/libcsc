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
    void enterScope(UID id, const CscStr &name) override;
    void leaveScope(UID id, const CscStr &name) override;
    void values(const CscStr &name, const VariableValues &values) override;
    CscStr toString();

private:
    int m_nest;
    std::stringstream m_buffer;

    void writeIndent();
    void writeValue(const CscStr &value,  ValueType type);
    ValueType arrayToValue(ValueType type);
};

CSC_END
#endif