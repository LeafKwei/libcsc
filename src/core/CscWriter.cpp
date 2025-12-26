#include "csc/core/CscWriter.hpp"
CSC_BEGIN

CscWriter::CscWriter(Context &context) : autoEnter_(false), context_(context){
    
}

CscWriter& CscWriter::autoEnterOn(){
    autoEnter_ = true;
    return *this;
}

CscWriter& CscWriter::autoEnterOff(){
    autoEnter_ = false;
    return *this;
}

CscWriter& CscWriter::makeScope(const String &name){
    context_.makeScope(name, autoEnter_);
    return *this;
}

CscWriter& CscWriter::enterScope(const String &name){
    context_.enterScope(name);
    return *this;
}

CscWriter& CscWriter::cleanScope(const String &name){
    context_.cleanScope(name);
    return *this;
}

CscWriter& CscWriter::leaveScope(){
    context_.leaveScope();
    return *this;
}

CscWriter& CscWriter::cleanVariable(const String &name){
    context_.cleanVariable(name);
    return *this;
}

CSC_END