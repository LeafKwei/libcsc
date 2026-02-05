#ifndef CSC_CORE_FUNCTIONS_HPP
#define CSC_CORE_FUNCTIONS_HPP

#include "csc/csc.hpp"
#include "csc/alias.hpp"
#include "csc/types.hpp"
#include "csc/context/types.hpp"
#include "csc/core/types.hpp"
CSC_BEGIN

/* 将ValueType类型的Value转换为C++类型的值 */
template<typename Tp>
inline Tp toCppValue(Value val, ValueType type){
    return Tp{}; //当Tp不在特例化范围内时，返回Tp的零值
}

template<>
inline bool toCppValue<bool>(Value val, ValueType type){
    if(type != ValType<bool>::valtype){
        throw CscExcept("Incompatible type to " + String(typeid(CppType<ValueType::Bool>::type).name()));
    }

    return std::any_cast<CppType<ValueType::Bool>::type>(val);
}

template<>
inline int toCppValue<int>(Value val, ValueType type){
    if(type != ValType<int>::valtype){
        throw CscExcept("Incompatible type to " + String(typeid(CppType<ValueType::Integer>::type).name()));
    }

    return static_cast<int>(std::any_cast<CppType<ValueType::Integer>::type>(val));
}

template<>
inline long toCppValue<long>(Value val, ValueType type){
    if(type != ValType<long>::valtype){
        throw CscExcept("Incompatible type to " + String(typeid(CppType<ValueType::Integer>::type).name()));
    }

    return std::any_cast<CppType<ValueType::Integer>::type>(val);
}

template<>
inline double toCppValue<double>(Value val, ValueType type){
    if(type != ValType<double>::valtype){
        throw CscExcept("Incompatible type to " + String(typeid(CppType<ValueType::Double>::type).name()));
    }

    return std::any_cast<CppType<ValueType::Double>::type>(val);
}

template<>
inline String toCppValue<String>(Value val, ValueType type){
    if(type != ValType<String>::valtype){
        throw CscExcept("Incompatible type to " + String(typeid(CppType<ValueType::String>::type).name()));
    }

    return std::any_cast<CppType<ValueType::String>::type>(val);
}

CSC_END
#endif