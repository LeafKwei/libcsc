#include "csc/context/val.hpp"
#include "csc/utility/utility.hpp"
#include "csc/core/CscString.hpp"
CSC_BEGIN

CscString::CscString(ScoQuerier querier, bool isroot){
    strfrom(querier, isroot);
}

String CscString::localstr(){
    return buffer_.str();
}

String CscString::strfrom(ScoQuerier querier, bool isroot){
    buffer_.str("");
    buffer_.clear();
    nest_ = 0;

    make(querier,  isroot);
    return buffer_.str();
}

/* 按深度优先算法遍历每个Scope */
void CscString::make(ScoQuerier querier, bool isroot){
    if(!isroot){  //只有在非root scope的情况下，才写入scope的名称到字符串中
        enterScope(querier.name());
    }

    /* 首先遍历Scope中的每个变量 */
    auto varsize = querier.sizeofVariables();
    decltype(varsize) varidx = 0;
    while(varidx < varsize){
        auto varq = querier.varquerier(varidx++);
        values(varq.name(), varq);
    }

    /* 再变遍历其中的每个Scope */
    auto scosize = querier.sizeofScopes();
    decltype(scosize) scoidx = 0;
    while(scoidx < scosize){
        auto scoq = querier.scoquerier(scoidx++);
        make(scoq, false);
    }

    if(!isroot){
        leaveScope(querier.name());
    }
}

void CscString::enterScope(const String &name){
    writeIndent();
    buffer_ << name << "::" << std::endl;
    ++nest_;
}

void CscString::leaveScope(const String &name){
    --nest_;
    writeIndent();
    buffer_ << "::" << name << std::endl;
}

void CscString::values(const String &name, const VarQuerier &querier){
    writeIndent();

    if(querier.size() == 1){                              //如果变量不是一个数组，则直接将变量名和变量值写入到buffer
        buffer_ << name << " = ";
        const auto &unit = querier.valueunit();
        writeValue(
            valueToString(unit.value, unit.type),
            unit.type
        );

        buffer_ << std::endl;
    }
    else{                                                             //否则按照数组格式处理，挨个处理每个值
        buffer_ << name << " = " << "{"; 

        for(Size_t index = 0; index < querier.size(); index++){
            if(index > 0) buffer_ << ", ";
            const auto &unit = querier.valueunit(index);
            writeValue(
                valueToString(unit.value, unit.type), 
                unit.type
            );
        }

        buffer_ << "}" << std::endl;
    }
}

void CscString::writeIndent(){
    for(int i = 0; i < nest_; i++){
        buffer_ << "\t";
    }
}

void CscString::writeValue(const String &value,  ValueType type){
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