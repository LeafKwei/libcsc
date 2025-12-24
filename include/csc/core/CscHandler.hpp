#ifndef CSC_HANDLER_HPP
#define CSC_HANDLER_HPP

#include "csc/csc.hpp"
#include "csc/context/Context.hpp"
#include "csc/context/ContextSeeker.hpp"
#include "csc/core/types.hpp"
#include "csc/core/CscEditor.hpp"
#include "csc/syntax/CmdDriver.hpp"
#include "csc/utility/utility.hpp"
#include "csc/utility/PathHelper.hpp"

CSC_BEGIN

/**
 * CscHandler是提供给用户使用的顶层接口，它的主要功能是以路径化访问的形式对作用域、变量的访问进行简化。同时，CscHandler也向用户提供了编辑Context的功能，
 * 并使用了CscEditor对其进行了封装。待编辑完成后，用户可通过调用toString函数得到字符串化的csc配置内容，并可将其写入文件实现持久化。
 */
class CscHandler{
public:
    CscHandler() =default;
    CscHandler(const String &script);

    bool               accessible(const String &path, bool v=false); /* 检查给定的路径是否可以访问。当v为true时，路径的最后一部分将被视为变量名称 */
    String             absolutePath();                                       /* 返回从根作用域到当前作用域的绝对路径 */
    CscHandler& enter(const String &path);                              /* 进入给定路径对应的作用域，如果路径为“/”，则进入根作用域 */
    CscHandler& iterate(ContextSeeker &seeker);            /* 从当前作用域开始，迭代其及所有子作用域的所有变量 */
    String            toString();                                               /* 从当前作用域开始，将其及子作用域、变量转换为字符串 */
    CscEditor       editor();                                                  /* 获取一个编辑器对象，可以编辑Context中的内容 */

    template<typename Tp>                                            /* 获取当前作用域中给定名称的变量值，类型参数Tp所支持的类型参见文档 */
    Tp getValue(const String &name);

    template<typename Tp>                                           /* 获取给定路径下的变量值，路径的最后一部分将被视为变量名称 */
    Tp enterAndGet(const String &path);

private:
    Context      context_;
    CmdDriver driver_;
};


//============= Templates =============
template<typename Tp>
inline Tp CscHandler::getValue(const String &name){
    throw CscExcept("Unsupported type.");
}

template<>
inline bool CscHandler::getValue<bool>(const String &name){
    const auto &unit = context_.getValueUnit(name);
    if(unit.type != ValueType::Bool){
        throw CscExcept("Incompatible type to " + String(typeid(CppType<ValueType::Bool>::type).name()));
    }

    return std::any_cast<CppType<ValueType::Bool>::type>(unit.value);
}

template<>
inline int CscHandler::getValue<int>(const String &name){
    const auto &unit = context_.getValueUnit(name);
    if(unit.type != ValueType::Integer){
        throw CscExcept("Incompatible type to " + String(typeid(int).name()));
    }

    return static_cast<int>(
        std::any_cast<CppType<ValueType::Integer>::type>(unit.value)
    );
}

template<>
inline long CscHandler::getValue<long>(const String &name){
    const auto &unit = context_.getValueUnit(name);
    if(unit.type != ValueType::Integer){
        throw CscExcept("Incompatible type to " + String(typeid(CppType<ValueType::Integer>::type).name()));
    }

    return std::any_cast<CppType<ValueType::Integer>::type>(unit.value);
}

template<>
inline double CscHandler::getValue<double>(const String &name){
    const auto &unit = context_.getValueUnit(name);
    if(unit.type != ValueType::Double){
        throw CscExcept("Incompatible type to " + String(typeid(CppType<ValueType::Double>::type).name()));
    }

    return std::any_cast<CppType<ValueType::Double>::type>(unit.value);
}

template<>
inline String CscHandler::getValue<String>(const String &name){
    const auto &unit = context_.getValueUnit(name);
    if(unit.type != ValueType::String){
        throw CscExcept("Incompatible type to " + String(typeid(CppType<ValueType::String>::type).name()));
    }

    return std::any_cast<CppType<ValueType::String>::type>(unit.value);
}

template<>
inline ArrBool CscHandler::getValue<ArrBool>(const String &name){
    ArrBool array;

    auto querier = context_.querier();
    querier.captureVariable(name);
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
inline ArrInt CscHandler::getValue<ArrInt>(const String &name){
    ArrInt array;

    auto querier = context_.querier();
    querier.captureVariable(name);
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
inline ArrLong CscHandler::getValue<ArrLong>(const String &name){
    ArrLong array;

    auto querier = context_.querier();
    querier.captureVariable(name);
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
inline ArrDouble CscHandler::getValue<ArrDouble>(const String &name){
    ArrDouble array;

    auto querier = context_.querier();
    querier.captureVariable(name);
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
inline ArrString CscHandler::getValue<ArrString>(const String &name){
    ArrString array;

    auto querier = context_.querier();
    querier.captureVariable(name);
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
inline Tp CscHandler::enterAndGet(const String &path){
    PathHelper helper(path);
    
    if(!helper.valid()){
        throw CscExcept("Invalid path: " + path);
    }

    auto endidx = (helper.size() > 0) ? helper.size() - 1 : 0;
    enter(helper.buildPath(endidx));

    return getValue<Tp>(helper.lastItem());
}

CSC_END
#endif