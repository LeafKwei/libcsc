#include "csc/core/CscEditor.hpp"
CSC_BEGIN

CscEditor::CscEditor(Context &context) : m_autoEnter(false), m_context(context){}

CscEditor& CscEditor::autoEnterOn(){
    m_autoEnter = true;
    return *this;
}

CscEditor& CscEditor::autoEnterOff(){
    m_autoEnter = false;
    return *this;
}

CscEditor& CscEditor::makeScope(const String &name){
    m_context.makeScope(name, m_autoEnter);
    return *this;
}

CscEditor& CscEditor::enterScope(const String &name){
    m_context.enterScope(name);
    return *this;
}

CscEditor& CscEditor::cleanScope(const String &name){
    m_context.cleanScope(name);
    return *this;
}

CscEditor& CscEditor::leaveScope(){
    m_context.leaveScope();
    return *this;
}

CscEditor& CscEditor::cleanVariable(const String &name){
    m_context.cleanVariable(name);
    return *this;
}

CSC_END