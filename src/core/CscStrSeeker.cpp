#include "csc/core/CscStrSeeker.hpp"
CSC_BEGIN

CscStrSeeker::CscStrSeeker() : m_nest(0){}

void CscStrSeeker::enterScope(const CscStr &name){
    writeIndent();
    m_buffer << name << "::" << std::endl;
    ++m_nest;
}

void CscStrSeeker::leaveScope(const CscStr &name){
    --m_nest;
    writeIndent();
    m_buffer << "::" << name << std::endl;
}

void CscStrSeeker::getVariable(const CscStr &name, const CscStr &value, ValueType type){
    writeIndent();
    switch(type){
        case ValueType::Bool:
        case ValueType::Integer:
        case ValueType::Double:
            m_buffer << name << " = " << value << std::endl;
            break;
        case ValueType::String:
        case ValueType::Unknown:
            m_buffer << name << " = " << "\"" << value << "\"" << std::endl;
            break;
        case ValueType::Bools:
        case ValueType::Integers:
        case ValueType::Doubles:
        case ValueType::Strings:
            m_buffer << name << " = " << "{" << value << "}" << std::endl;
            break;
    }
}

CscStr CscStrSeeker::toString(){
    return m_buffer.str();
}

void CscStrSeeker::writeIndent(){
    for(int i = 0; i < m_nest; i++){
        m_buffer << "\t";
    }
}

CSC_END