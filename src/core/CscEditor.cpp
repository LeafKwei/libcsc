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

CscEditor& CscEditor::makeScope(crString name){
    m_context.makeScope(name, m_autoEnter);
    return *this;
}

CscEditor& CscEditor::enterScope(crString name){
    m_context.enterScope(name);
    return *this;
}

CscEditor& CscEditor::cleanScope(crString name){
    m_context.cleanScope(name);
    return *this;
}

CscEditor& CscEditor::leaveScope(){
    m_context.leaveScope();
    return *this;
}

CscEditor& CscEditor::makeVariable(crString name, InitValues values, ValueType type){
    m_context.makeVariable(name, values, type);
    return *this;
}

CscEditor& CscEditor::extendValues(crString name, InitValues values){
    m_context.extendValues(name, values);
    return *this;
}

CscEditor& CscEditor::cleanVariable(crString name){
    m_context.cleanVariable(name);
    return *this;
}

CSC_END