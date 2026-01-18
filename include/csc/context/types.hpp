#ifndef CSC_CONTEXT_TYPES_HPP
#define CSC_CONTEXT_TYPES_HPP

#include <variant>
#include <map>
#include <vector>
#include <memory>
#include "csc/csc.hpp"
#include "csc/alias.hpp"
CSC_BEGIN

/* Context支持的数据的类型对应的枚举 */
enum class ValueType{
    Unknown, 
    Bool, Integer, Double, String,        //bool、int/long、double、std::string
};

////////////////////////////////////////////////////////////////////////////////////////类型映射
/* 通过下方的模板将ValueType的类型映射为C++内建类型，以此将枚举值与这些类型绑定 */
template<ValueType VTP>
struct CppType{};

template<>
struct CppType<ValueType::Bool>{
    using type = bool;
};

template<>
struct CppType<ValueType::Integer>{
    using type = long;
};

template<>
struct CppType<ValueType::Double>{
    using type = double;
};

template<>
struct CppType<ValueType::String>{
    using type = String;
};

/* 通过下方的模板将C++内建类型映射为ValueType枚举值 */
template<typename CTP>
struct ValType{};

template<>
struct ValType<bool>{
    static constexpr ValueType valtype = ValueType::Bool;
};

template<>
struct ValType<int>{
    static constexpr ValueType valtype = ValueType::Integer;
};

template<>
struct ValType<long>{
    static constexpr ValueType valtype = ValueType::Integer;
};

template<>
struct ValType<double>{
    static constexpr ValueType valtype = ValueType::Double;
};

template<>
struct ValType<String>{
    static constexpr ValueType valtype = ValueType::String;
};


////////////////////////////////////////////////////////////////////////////////////////别名
/* 声明一些常用的别名 */
struct Variable;
struct Scope;
using Value = std::any;
using VariablePtr = std::shared_ptr<Variable>;
using VariableWkr = std::weak_ptr<Variable>;
using ValueKeeper = std::vector<Value>;

////////////////////////////////////////////////////////////////////////////////////////结构体定义
struct Variable{
    String name;
    ValueKeeper values;
    ValueType type;
};

struct ValueUnit{
    Value value;
    ValueType type;
};

CSC_END
#endif