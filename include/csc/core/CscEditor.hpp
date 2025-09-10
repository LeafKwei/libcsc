#ifndef CSC_EDITOR_HPP
#define CSC_EDITOR_HPP

#include "csc/context/Context.hpp"
CSC_BEGIN

class CscEditor{
public:
    using InitValues = std::initializer_list<CscStr>;

public:
    CscEditor(Context &context);

    CscEditor& autoEnterOn();                  /* Enable auto-enter. Enter scope automatically when it was made. */
    CscEditor& autoEnterOff();                  /* Disable auto-enter. */
    CscEditor& makeScope(ConstStr name);
    CscEditor& enterScope(ConstStr name);
    CscEditor& leaveScope();
    CscEditor& cleanScope(ConstStr name);
    CscEditor& makeVariable(ConstStr name, InitValues values, ValueType type);
    CscEditor& extendValues(ConstStr name, InitValues values);
    CscEditor& cleanVariable(ConstStr name);

private:
    bool m_autoEnter;
    Context &m_context;
};

CSC_END
#endif