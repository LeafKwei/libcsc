#include "csc/core/CscStrSeeker.hpp"
#include "csc/utility/utility.hpp"
CSC_BEGIN

CscStrSeeker::CscStrSeeker() : m_nest(0){}

void CscStrSeeker::enterScope(UID id, crString name){
    writeIndent();
    m_buffer << name << "::" << std::endl;
    ++m_nest;
}

void CscStrSeeker::leaveScope(UID id, crString name){
    --m_nest;
    writeIndent();
    m_buffer << "::" << name << std::endl;
}

void CscStrSeeker::values(crString name, const VariableValues &values){
    writeIndent();

    if(values.size() == 1){                //如果变量不是一个数组，则直接将变量名和变量值写入到buffer
        m_buffer << name << " = ";
        writeValue(
            valueToString(values.val(), values.type()), 
            values.type()
        );

        m_buffer << std::endl;
    }
    else{                                                             //否则按照数组格式处理
        m_buffer << name << " = " << "{"; 

        for(Size_t index = 0; index < values.size(); index++){
            if(index > 1) m_buffer << ", ";
            writeValue(
                valueToString(values.val(index), values.type()), 
                values.type()
            );
        }

        m_buffer << "}" << std::endl;
    }
}

String CscStrSeeker::toString(){
    return m_buffer.str();
}

void CscStrSeeker::writeIndent(){
    for(int i = 0; i < m_nest; i++){
        m_buffer << "\t";
    }
}

void CscStrSeeker::writeValue(crString value,  ValueType type){
    switch(type){
        case ValueType::Bool:
        case ValueType::Integer:
        case ValueType::Double:
            m_buffer << value;
            break;
        case ValueType::String:
            m_buffer << "\"" << toEscapingString(value) << "\"";
            break;
        case ValueType::Unknown:
            m_buffer << "*** UNKNOWN VALUE ***";
        default:
            break;
    }
}

CSC_END