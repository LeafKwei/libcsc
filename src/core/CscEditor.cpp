#include "csc/core/CscEditor.hpp"
CSC_BEGIN

CscEditor::CscEditor(Context &context) : autoEnter_(false), context_(context){}

CscEditor& CscEditor::autoEnterOn(){
    autoEnter_ = true;
    return *this;
}

CscEditor& CscEditor::autoEnterOff(){
    autoEnter_ = false;
    return *this;
}

CscEditor& CscEditor::makeScope(const String &name){
    context_.makeScope(name, autoEnter_);
    return *this;
}

CscEditor& CscEditor::enterScope(const String &name){
    context_.enterScope(name);
    return *this;
}

CscEditor& CscEditor::cleanScope(const String &name){
    context_.cleanScope(name);
    return *this;
}

CscEditor& CscEditor::leaveScope(){
    context_.leaveScope();
    return *this;
}

CscEditor& CscEditor::cleanVariable(const String &name){
    context_.cleanVariable(name);
    return *this;
}

CSC_END