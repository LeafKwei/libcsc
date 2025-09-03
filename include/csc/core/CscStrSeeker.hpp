#ifndef CSC_STRSEEKER_HPP
#define CSC_STRSEEKER_HPP

#include <iostream>
#include <sstream>
#include "csc/context/ContextSeeker.hpp"
CSC_BEGIN

class CscStrSeeker : public ContextSeeker{
public:
    CscStrSeeker();
    void enterScope(const CscStr &name) override;
    void leaveScope(const CscStr &name) override;
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