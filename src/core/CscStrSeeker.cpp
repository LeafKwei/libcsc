#include "csc/core/CscStrSeeker.hpp"
#include "csc/utility/utility.hpp"
CSC_BEGIN

CscStrSeeker::CscStrSeeker() : m_nest(0){}

void CscStrSeeker::enterScope(UID id, const CscStr &name){
    writeIndent();
    m_buffer << name << "::" << std::endl;
    ++m_nest;
}

void CscStrSeeker::leaveScope(UID id, const CscStr &name){
    --m_nest;
    writeIndent();
    m_buffer << "::" << name << std::endl;
}

void CscStrSeeker::values(const CscStr &name, const VariableValues &values){
    writeIndent();
    
    auto vtype = arrayToValue(values.type());
    if(vtype == ValueType::Unknown){                //如果变量不是一个数组，则直接将变量名和变量值写入到buffer
        m_buffer << name << " = ";
        writeValue(values.str(), values.type());
        m_buffer << std::endl;
        return;
    }

    m_buffer << name << " = " << "{";            //否则按照数组格式处理

    /* ArrayAssignCommand在处理对数组的赋值时，会首先保存一个空字符串作为占位元素(目的是省去Context对空变量的检查)，因此此处需要让index为1忽略首个数组值 */
    for(Size_t index = 1; index < values.size(); index++){
        if(index > 1) m_buffer << ", ";
        writeValue(values.str(index), vtype);
    }

    m_buffer << "}" << std::endl;
}

CscStr CscStrSeeker::toString(){
    return m_buffer.str();
}

void CscStrSeeker::writeIndent(){
    for(int i = 0; i < m_nest; i++){
        m_buffer << "\t";
    }
}

void CscStrSeeker::writeValue(const CscStr &value,  ValueType type){
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

ValueType CscStrSeeker::arrayToValue(ValueType type){
    switch(type){
        case ValueType::Bools:
            return ValueType::Bool;
        case ValueType::Integers:
            return ValueType::Integer;
        case ValueType::Doubles:
            return ValueType::Double;
        case ValueType::Strings:
            return ValueType::String;
        default:
            return ValueType::Unknown;
    }
}

CSC_END