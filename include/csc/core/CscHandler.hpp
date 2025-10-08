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
    CscHandler(crString script);

    bool               accessible(crString path, bool v=false); /* 检查给定的路径是否可以访问。当v为true时，路径的最后一部分将被视为变量名称 */
    String            absolutePath();                                       /* 返回从根作用域到当前作用域的绝对路径 */
    CscHandler& enter(crString path);                              /* 进入给定路径对应的作用域，如果路径为“/”，则进入根作用域 */
    CscHandler& iterate(ContextSeeker &seeker);            /* 从当前作用域开始，迭代其及所有子作用域的所有变量 */
    String            toString();                                               /* 从当前作用域开始，将其及子作用域、变量转换为字符串 */
    CscEditor       editor();                                                  /* 获取一个编辑器对象，可以编辑Context中的内容 */

    template<typename Tp>                                            /* 获取当前作用域中给定名称的变量值，类型参数Tp所支持的类型参见文档 */
    Tp getValue(crString name);

    template<typename Tp>                                           /* 获取给定路径下的变量值，路径的最后一部分将被视为变量名称 */
    Tp enterAndGet(crString path);

private:
    Context      m_context;
    CmdDriver m_driver;

    bool do_accessibleScope(crString path);
    bool do_accessibleVariable(crString path);
    void do_enter(const PathItems &items);
};


//============= Templates =============
template<typename Tp>
inline Tp getValue(crString name){
    throw CscExcept("Unsupported type.");
}

template<>
inline bool CscHandler::getValue<bool>(crString name){
    const auto &value = m_context.getValue(name);
    if(value.type != ValueType::Bool){
        throw CscExcept("Incompatible type to " + String(typeid(CppType<ValueType::Bool>).name()));
    }

    return std::any_cast<CppType<ValueType::Bool>::type>(value);
}

template<>
inline int CscHandler::getValue<int>(crString name){
    const auto &value = m_context.getValue(name);
    if(value.type != ValueType::Integer){
        throw CscExcept("Incompatible type to " + String(typeid(int).name()));
    }

    return static_cast<int>(
        std::any_cast<CppType<ValueType::Integer>::type>(value)
    );
}

template<>
inline long CscHandler::getValue<long>(crString name){
    const auto &value = m_context.getValue(name);
    if(value.type != ValueType::Integer){
        throw CscExcept("Incompatible type to " + String(typeid(CppType<ValueType::Integer>).name()));
    }

    return std::any_cast<CppType<ValueType::Integer>::type>(value);
}

template<>
inline double CscHandler::getValue<double>(crString name){
    const auto &value = m_context.getValue(name);
    if(value.type != ValueType::Double){
        throw CscExcept("Incompatible type to " + String(typeid(CppType<ValueType::Double>).name()));
    }

    return std::any_cast<CppType<ValueType::Double>::type>(value);
}

template<>
inline String CscHandler::getValue<String>(crString name){
    const auto &value = m_context.getValue(name);
    if(value.type != ValueType::String){
        throw CscExcept("Incompatible type to " + String(typeid(CppType<ValueType::String>).name()));
    }

    return std::any_cast<CppType<ValueType::String>::type>(value);
}

template<>
inline array_bool CscHandler::getValue<array_bool>(crString name){
    array_bool array;

    const auto &values = m_context.getValues(name);
    if(values.type() != ValueType::Bool){
        throw CscExcept("Incompatible type to " + String(typeid(CppType<ValueType::Bool>).name()));
    }

    for(Size_t index = 0; index < values.size(); index++){
        array.push_back(
            std::any_cast<CppType<ValueType::Bool>::type>(values.val(index))
        );
    }

    return array;
}

template<>
inline array_int CscHandler::getValue<array_int>(crString name){
    array_int array;

    const auto &values = m_context.getValues(name);
    if(values.type() != ValueType::Integer){
        throw CscExcept("Incompatible type to " + String(typeid(int).name()));
    }

    for(Size_t index = 0; index < values.size(); index++){
        array.push_back(
            static_cast<int>(
                std::any_cast<CppType<ValueType::Integer>::type>(values.val(index))
            )
        );
    }

    return array;
}

template<>
inline array_long CscHandler::getValue<array_long>(crString name){
    array_long array;

    const auto &values = m_context.getValues(name);
    if(values.type() != ValueType::Integer){
        throw CscExcept("Incompatible type to " + String(typeid(CppType<ValueType::Integer>).name()));
    }

    for(Size_t index = 0; index < values.size(); index++){
        array.push_back(
            std::any_cast<CppType<ValueType::Integer>::type>(values.val(index))
        );
    }

    return array;
}

template<>
inline array_double CscHandler::getValue<array_double>(crString name){
    array_double array;

    const auto &values = m_context.getValues(name);
    if(values.type() != ValueType::Double){
        throw CscExcept("Incompatible type to " + String(typeid(CppType<ValueType::Double>).name()));
    }

    for(Size_t index = 0; index < values.size(); index++){
        array.push_back(
            std::any_cast<CppType<ValueType::Double>::type>(values.val(index))
        );
    }

    return array;
}

template<>
inline array_string CscHandler::getValue<array_string>(crString name){
    array_string array;

    const auto &values = m_context.getValues(name);
    if(values.type() != ValueType::String){
        throw CscExcept("Incompatible type to " + String(typeid(CppType<ValueType::String>).name()));
    }

    for(Size_t index = 0; index < values.size(); index++){
        array.push_back(
            std::any_cast<CppType<ValueType::String>::type>(values.val(index))
        );
    }

    return array;
}

template<typename Tp>
inline Tp CscHandler::enterAndGet(crString path){
    const auto &items = detachName(path);

    if(items.first.size() != 0){
        enter(items.first);
    }
    
    return getValue<Tp>(items.second);
}

CSC_END
#endif