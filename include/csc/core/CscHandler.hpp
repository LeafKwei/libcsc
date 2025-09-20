#ifndef CSC_HANDLER_HPP
#define CSC_HANDLER_HPP

#include "csc/csc.hpp"
#include "csc/context/Context.hpp"
#include "csc/context/ContextSeeker.hpp"
#include "csc/core/types.hpp"
#include "csc/core/CscEditor.hpp"
#include "csc/core/functions.hpp"
#include "csc/syntax/CmdDriver.hpp"
#include "csc/utility/utility.hpp"

CSC_BEGIN

/**
 * CscHandler是提供给用户使用的顶层接口，它的主要功能是以路径化访问的形式对作用域、变量的访问进行简化。同时，CscHandler也向用户提供了编辑Context的功能，
 * 并使用了CscEditor对其进行了封装。待编辑完成后，用户可通过调用toString函数得到字符串化的csc配置内容，并可将其写入文件实现持久化。
 */
class CscHandler{
public:
    using PathItems = decltype(splitPath(""));

public:
    CscHandler() =default;
    CscHandler(ConstStr script);

    bool               accessible(ConstStr path, bool v=false); /* 检查给定的路径是否可以访问。当v为true时，路径的最后一部分将被视为变量名称 */
    CscStr            absolutePath();                                       /* 返回从根作用域到当前作用域的绝对路径 */
    CscHandler& enter(ConstStr path);                              /* 进入给定路径对应的作用域，如果路径为“/”，则进入根作用域 */
    CscHandler& iterate(ContextSeeker &seeker);            /* 从当前作用域开始，迭代其及所有子作用域的所有变量 */
    CscStr            toString();                                               /* 从当前作用域开始，将其及子作用域、变量转换为字符串 */
    CscEditor       editor();                                                  /* 获取一个编辑器对象，可以编辑Context中的内容 */

    template<typename Tp>                                            /* 获取当前作用域中给定名称的变量值，类型参数Tp所支持的类型参见文档 */
    Tp getValue(ConstStr name);

    template<typename Tp>                                           /* 获取给定路径下的变量值，路径的最后一部分将被视为变量名称 */
    Tp enterAndGet(ConstStr path);

private:
    Context      m_context;
    CmdDriver m_driver;

    bool do_accessibleScope(ConstStr path);
    bool do_accessibleVariable(ConstStr path);
    void do_enter(const PathItems &items);
};


//============= Templates =============
template<typename Tp>
inline Tp getValue(ConstStr name){
    throw CscExcept("Unsupported type.");
}

template<>
inline bool CscHandler::getValue<bool>(ConstStr name){
    const auto &value = m_context.getValue(name);
    if(value.type != ValueType::Bool){
        throw CscExcept("Incompatible type.");
    }

    return value.str == "true" ? true : false;
}

template<>
inline int CscHandler::getValue<int>(ConstStr name){
    const auto &value = m_context.getValue(name);
    if(value.type != ValueType::Integer){
        throw CscExcept("Incompatible type.");
    }

    return static_cast<int>(std::strtol(value.str.c_str(), NULL, baseOf(value.str)));
}

template<>
inline long CscHandler::getValue<long>(ConstStr name){
    const auto &value = m_context.getValue(name);
    if(value.type != ValueType::Integer){
        throw CscExcept("Incompatible type.");
    }

    return std::strtol(value.str.c_str(), NULL, baseOf(value.str));
}

template<>
inline double CscHandler::getValue<double>(ConstStr name){
    const auto &value = m_context.getValue(name);
    if(value.type != ValueType::Double){
        throw CscExcept("Incompatible type.");
    }

    return std::strtod(value.str.c_str(), NULL);
}

template<>
inline CscStr CscHandler::getValue<CscStr>(ConstStr name){
    return m_context.getValue(name).str;
}

template<>
inline array_bool CscHandler::getValue<array_bool>(ConstStr name){
    array_bool array;

    auto values = m_context.getValues(name);
    if(values.type() != ValueType::Bools){
        throw CscExcept("Incompatible type.");
    }

    for(Size_t i = 1; i < values.size(); i++){
        auto r = values.str(i) == "true" ? true : false;
        array.push_back(r);
    }
}

template<>
inline array_int CscHandler::getValue<array_int>(ConstStr name){
    array_int array;

    auto values = m_context.getValues(name);
    if(values.type() != ValueType::Integers){
        throw CscExcept("Incompatible type.");
    }

    for(Size_t i = 1; i < values.size(); i++){
        const auto &v = values.str(i);
        auto r = static_cast<int>(std::strtol(v.c_str(), NULL, baseOf(v)));
        array.push_back(r);
    }
}

template<>
inline array_long CscHandler::getValue<array_long>(ConstStr name){
    array_long array;

    auto values = m_context.getValues(name);
    if(values.type() != ValueType::Integers){
        throw CscExcept("Incompatible type.");
    }

    for(Size_t i = 1; i < values.size(); i++){
        const auto &v = values.str(i);
        auto r = std::strtol(v.c_str(), NULL, baseOf(v));
        array.push_back(r);
    }
}

template<>
inline array_double CscHandler::getValue<array_double>(ConstStr name){
    array_long array;

    auto values = m_context.getValues(name);
    if(values.type() != ValueType::Doubles){
        throw CscExcept("Incompatible type.");
    }

    for(Size_t i = 1; i < values.size(); i++){
        const auto &v = values.str(i);
        auto r = std::strtol(v.c_str(), NULL, baseOf(v));
        array.push_back(r);
    }
}

template<>
inline array_string CscHandler::getValue<array_string>(ConstStr name){
    array_string array;

    auto values = m_context.getValues(name);
    if(values.type() != ValueType::Strings){
        throw CscExcept("Incompatible type.");
    }

    for(Size_t i = 1; i < values.size(); i++){
        const auto &v = values.str(i);
        array.push_back(v);
    }
}

template<typename Tp>
inline Tp CscHandler::enterAndGet(ConstStr path){
    const auto &items = detachName(path);

    if(items.first.size() != 0){
        enter(items.first);
    }
    
    return getValue<Tp>(items.second);
}

CSC_END
#endif