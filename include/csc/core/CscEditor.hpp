#ifndef CSC_EDITOR_HPP
#define CSC_EDITOR_HPP

#include "csc/context/Context.hpp"
CSC_BEGIN

class CscEditor{
public:
    CscEditor(Context &context);

private:
    Context &m_context;
};

CSC_END
#endif