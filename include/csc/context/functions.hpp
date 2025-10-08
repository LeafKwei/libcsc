#ifndef CSC_CONTEXT_FUNCTIONS_HPP
#define CSC_CONTEXT_FUNCTIONS_HPP

#include "csc/csc.hpp"
#include "csc/context/types.hpp"
CSC_BEGIN

inline VariableValue zeroValue(ValueType type){
    switch(type){
        case ValueType::Bool:
            return VariableValue{bool{}, type};
        case ValueType::Integer:
            return VariableValue{long{}, type};
        case ValueType::Double:
            return VariableValue{double{}, type};
        case ValueType::String:
            return VariableValue{String{}, type};
        default:
            return Context::VarValue{};
    };
}

CSC_END
#endif