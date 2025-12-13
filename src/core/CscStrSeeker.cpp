#include "csc/core/CscStrSeeker.hpp"
#include "csc/utility/utility.hpp"
CSC_BEGIN

CscStrSeeker::CscStrSeeker() : nest_(0){}

void CscStrSeeker::enterScope(UID id, const String &name){
    writeIndent();
    buffer_ << name << "::" << std::endl;
    ++nest_;
}

void CscStrSeeker::leaveScope(UID id, const String &name){
    --nest_;
    writeIndent();
    buffer_ << "::" << name << std::endl;
}

void CscStrSeeker::values(const String &name, const ValueAccessor &accessor){
    writeIndent();

    if(accessor.size() == 1){                              //如果变量不是一个数组，则直接将变量名和变量值写入到buffer
        buffer_ << name << " = ";
        writeValue(
            valueToString(accessor.value(), accessor.type()), 
            accessor.type()
        );

        buffer_ << std::endl;
    }
    else{                                                             //否则按照数组格式处理，挨个处理每个值
        buffer_ << name << " = " << "{"; 

        for(Size_t index = 0; index < accessor.size(); index++){
            if(index > 0) buffer_ << ", ";
            writeValue(
                valueToString(accessor.value(index), accessor.type()), 
                accessor.type()
            );
        }

        buffer_ << "}" << std::endl;
    }
}

String CscStrSeeker::toString(){
    return buffer_.str();
}

void CscStrSeeker::writeIndent(){
    for(int i = 0; i < nest_; i++){
        buffer_ << "\t";
    }
}

void CscStrSeeker::writeValue(const String &value,  ValueType type){
    switch(type){
        case ValueType::Bool:
        case ValueType::Integer:
        case ValueType::Double:
            buffer_ << value;
            break;
        case ValueType::String:
            buffer_ << "\"" << toEscapingString(value) << "\"";
            break;
        case ValueType::Unknown:
            buffer_ << "*** UNKNOWN VALUE ***";
        default:
            break;
    }
}

CSC_END