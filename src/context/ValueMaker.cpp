#include "csc/context/types.hpp"
#include "csc/context/ValueMaker.hpp"
#include "csc/utility/utility.hpp"
CSC_BEGIN

Value ValueMaker::makeZero(ValueType type){
    switch(type){
        case ValueType::Bool:
            return CppType<ValueType::Bool>::type{};
        case ValueType::Integer:
            return CppType<ValueType::Integer>::type{};
        case ValueType::Double:
            return CppType<ValueType::Double>::type{};
        case ValueType::String:
            return CppType<ValueType::String>::type{};
        default:
            return Value{};
    }
}


CSC_END