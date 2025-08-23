#ifndef CSC_STRITERATOR_HPP
#define CSC_STRITERATOR_HPP

#include <iostream>
#include <sstream>
#include "csc/context/ContextSeeker.hpp"
CSC_BEGIN

class CscStrSeeker : public ContextSeeker{
public:
    CscStrSeeker();
    void enterScope(const CscStr &name) override;
    void leaveScope(const CscStr &name) override;
    void getVariable(const CscStr &name, const CscStr &value, ValueType type) override;
    CscStr toString();

private:
    int m_nest;
    std::stringstream m_buffer;

    void writeIndent();
};

CSC_END
#endif