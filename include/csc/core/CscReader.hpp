#ifndef CSC_READER_HPP
#define CSC_READER_HPP

#include "csc/types.hpp"
#include "csc/core/types.hpp"
#include "csc/context/Context.hpp"
#include "csc/utility/PathHelper.hpp"
CSC_BEGIN

class CscReader{
public:
    CscReader(Context &context);
    bool     accessible(const String &path, bool v=false) const; /* 检查给定的路径是否可以访问。当v为true时，路径的最后一部分将被视为变量名称 */
    void     enter(const String &path) const;                               /* 进入给定路径对应的作用域，如果路径为“/”，则进入根作用域 */
    Walker walker() const;                                                             /* 获取当前作用域的漫步器以迭代其中的内容 */
    String  toString() const;                                                         /* 从当前作用域开始，将其及子作用域、变量转换为字符串 */

    template<typename Tp>                                            /* 获取当前作用域中给定名称的变量值，类型参数Tp所支持的类型参见文档 */
    Tp getValue(const String &name) const;

    template<typename Tp>                                           /* 获取给定路径下的变量值，路径的最后一部分将被视为变量名称 */
    Tp enterAndGet(const String &path) const;

private:
    Context &context_;
};

////////////////////////////////////////////////////////////////////////////////////////特例化
template<typename Tp>
inline Tp CscReader::getValue(const String &name) const{
    throw CscExcept("Unsupported type.");
}

template<>
inline bool CscReader::getValue<bool>(const String &name) const{
    const auto &unit = context_.getValueUnit(name);
    if(unit.type != ValueType::Bool){
        throw CscExcept("Incompatible type to " + String(typeid(CppType<ValueType::Bool>::type).name()));
    }

    return std::any_cast<CppType<ValueType::Bool>::type>(unit.value);
}

template<>
inline int CscReader::getValue<int>(const String &name) const{
    const auto &unit = context_.getValueUnit(name);
    if(unit.type != ValueType::Integer){
        throw CscExcept("Incompatible type to " + String(typeid(int).name()));
    }

    return static_cast<int>(
        std::any_cast<CppType<ValueType::Integer>::type>(unit.value)
    );
}

template<>
inline long CscReader::getValue<long>(const String &name) const{
    const auto &unit = context_.getValueUnit(name);
    if(unit.type != ValueType::Integer){
        throw CscExcept("Incompatible type to " + String(typeid(CppType<ValueType::Integer>::type).name()));
    }

    return std::any_cast<CppType<ValueType::Integer>::type>(unit.value);
}

template<>
inline double CscReader::getValue<double>(const String &name) const{
    const auto &unit = context_.getValueUnit(name);
    if(unit.type != ValueType::Double){
        throw CscExcept("Incompatible type to " + String(typeid(CppType<ValueType::Double>::type).name()));
    }

    return std::any_cast<CppType<ValueType::Double>::type>(unit.value);
}

template<>
inline String CscReader::getValue<String>(const String &name) const{
    const auto &unit = context_.getValueUnit(name);
    if(unit.type != ValueType::String){
        throw CscExcept("Incompatible type to " + String(typeid(CppType<ValueType::String>::type).name()));
    }

    return std::any_cast<CppType<ValueType::String>::type>(unit.value);
}

template<>
inline ArrBool CscReader::getValue<ArrBool>(const String &name) const{
    ArrBool array;

    auto querier = context_.querier(name);
    if(querier.queryType() != ValueType::Bool){
        throw CscExcept("Incompatible type to " + String(typeid(CppType<ValueType::Bool>::type).name()));
    }

    for(Size_t index = 0; index < querier.querySize(); index++){
        array.push_back(
            std::any_cast<CppType<ValueType::Bool>::type>(querier.queryValue(index))
        );
    }

    return array;
}

template<>
inline ArrInt CscReader::getValue<ArrInt>(const String &name) const{
    ArrInt array;

    auto querier = context_.querier(name);
    if(querier.queryType() != ValueType::Integer){
        throw CscExcept("Incompatible type to " + String(typeid(int).name()));
    }

    for(Size_t index = 0; index < querier.querySize(); index++){
        array.push_back(
            static_cast<int>(
                std::any_cast<CppType<ValueType::Integer>::type>(querier.queryValue(index))
            )
        );
    }

    return array;
}

template<>
inline ArrLong CscReader::getValue<ArrLong>(const String &name) const{
    ArrLong array;

    auto querier = context_.querier(name);
    if(querier.queryType() != ValueType::Integer){
        throw CscExcept("Incompatible type to " + String(typeid(CppType<ValueType::Integer>::type).name()));
    }

    for(Size_t index = 0; index < querier.querySize(); index++){
        array.push_back(
            std::any_cast<CppType<ValueType::Integer>::type>(querier.queryValue(index))
        );
    }

    return array;
}

template<>
inline ArrDouble CscReader::getValue<ArrDouble>(const String &name) const{
    ArrDouble array;

    auto querier = context_.querier(name);
    if(querier.queryType() != ValueType::Double){
        throw CscExcept("Incompatible type to " + String(typeid(CppType<ValueType::Double>::type).name()));
    }

    for(Size_t index = 0; index < querier.querySize(); index++){
        array.push_back(
            std::any_cast<CppType<ValueType::Double>::type>(querier.queryValue(index))
        );
    }

    return array;
}

template<>
inline ArrString CscReader::getValue<ArrString>(const String &name) const{
    ArrString array;

    auto querier = context_.querier(name);
    if(querier.queryType() != ValueType::String){
        throw CscExcept("Incompatible type to " + String(typeid(CppType<ValueType::String>::type).name()));
    }

    for(Size_t index = 0; index < querier.querySize(); index++){
        array.push_back(
            std::any_cast<CppType<ValueType::String>::type>(querier.queryValue(index))
        );
    }

    return array;
}

template<typename Tp>
inline Tp CscReader::enterAndGet(const String &path) const{
    PathHelper helper(path);
    
    if(!helper.valid()){
        throw CscExcept("Invalid path: " + path);
    }

    /* 如果path仅是一个根路径，则视为错误 */
    if(helper.rootonly()){
        throw CscExcept("No variable name provided.");
    }

    /* 如果path存在dirname部分，则先进入对应路径下 */
    if(helper.complex()){
        enter(helper.dirname());
    }
    
    return getValue<Tp>(helper.basename());
}

CSC_END
#endif