#ifndef CSC_CORE_TYPES_HPP
#define CSC_CORE_TYPES_HPP

#include <vector>
#include <memory>
#include <map>
#include "csc/csc.hpp"
#include "csc/alias.hpp"
#include "csc/context/types.hpp"
CSC_BEGIN

/**
 * 下方的别名被用于CscHandler::getValue系列函数，如果Context中保存的variable具有多个值，可以通过为getValue指定下方的类型来获取一个vector。
 * csc目前仅支持bool、int/long(底层都使用long，但是用户可以选择按int转换)、double、std::string四种类型的数据，在context/types.hpp中定义了
 * 枚举ValueType，用于在Context中标记std::any中存储的是何种类型的数据
 */
using ArrBool      = std::vector<CppType<ValueType::Bool>::type>;
using ArrInt         = std::vector<int>;                                                          //当修改了这里时，也记得修改core/functions中的模板
using ArrLong     = std::vector<CppType<ValueType::Integer>::type>;
using ArrDouble = std::vector<CppType<ValueType::Double>::type>;
using ArrString   = std::vector<CppType<ValueType::String>::type>;

////////////////////////////////////////////////////////////////////////////////////////类型映射
/* 通过下方的模板将Arr*类型映射为其元素类型 */
template<typename ATP>
struct ElemType{
};

template<>
struct ElemType<ArrBool>{
    using type = CppType<ValueType::Bool>::type;
};

template<>
struct ElemType<ArrInt>{
    using type = CppType<ValueType::Integer>::type;
};

template<>
struct ElemType<ArrLong>{
    using type = CppType<ValueType::Integer>::type;
};

template<>
struct ElemType<ArrDouble>{
    using type = CppType<ValueType::Double>::type;
};

template<>
struct ElemType<ArrString>{
    using type = CppType<ValueType::String>::type;
};


CSC_END
#endif