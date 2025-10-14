#ifndef CSC_EDITOR_HPP
#define CSC_EDITOR_HPP

#include <utility>
#include "csc/context/Context.hpp"
CSC_BEGIN

 /**
  * CscEditor是对Context的封装，旨在向用户提供更精简的操作Context的功能，用户可通过使用CscEditor来编辑Context中的内容，
  * 由此来改变通过CscHandler::toString函数产生的csc配置文件的内容。
  */
class CscEditor{
public:
    CscEditor(Context &context);

    CscEditor& autoEnterOn();                  /* 启用自动进入作用域的功能，当makeScope函数创建作用域后，自动进入该作用域 */
    CscEditor& autoEnterOff();                  /* 禁用自动进入作用域的功能(默认) */
    CscEditor& makeScope(crString name);
    CscEditor& enterScope(crString name);
    CscEditor& leaveScope();
    CscEditor& cleanScope(crString name);

    template<typename... T>
    CscEditor& makeVariable(crString name, ValueType type, T &&...values);
    template<typename... T>
    CscEditor& makeVariable(crString name, ValueType type, int value1, T &&...values);                //通过重载函数模板并将value1指定为int，从而让编译器优先选择此版本处理int类型的数据
    template<typename... T>
    CscEditor& makeVariable(crString name, ValueType type, const char *value1, T &&...values);  //通过重载函数模板并将value1指定为const char*，从而让编译器优先选择此版本处理char*类型的数据
    template<typename... T>
    CscEditor& extendValues(crString name, T &&...values);
    template<typename... T>
    CscEditor& extendValues(crString name, int value1, T &&...values);
    template<typename... T>
    CscEditor& extendValues(crString name, const char *value1, T &&...values);

    CscEditor& cleanVariable(crString name);

private:
    bool m_autoEnter;
    Context &m_context;
};

template<typename... T>
inline CscEditor& CscEditor::makeVariable(crString name, ValueType type, T &&...values){
    m_context.makeVariable(name, type, {std::forward<T>(values)...});
    return *this;
}

template<typename... T>
inline CscEditor& CscEditor::makeVariable(crString name, ValueType type, int value1, T &&...values){
    m_context.makeVariable(
        name, 
        type,
        {CppType<ValueType::Integer>::type{value1}, CppType<ValueType::Integer>::type{std::forward<T>(values)}...}
    );

    return *this;
}

template<typename... T>
inline CscEditor& CscEditor::makeVariable(crString name, ValueType type, const char *value1, T &&...values){
    m_context.makeVariable(
        name, 
        type,
        {CppType<ValueType::String>::type{value1}, CppType<ValueType::String>::type{std::forward<T>(values)}...}
    );

    return *this;
}

template<typename... T>
inline CscEditor& CscEditor::extendValues(crString name, T &&...values){
    m_context.extendValues(name, {std::forward<T>(values)...});
    return *this;
}

template<typename... T>
inline CscEditor& CscEditor::extendValues(crString name, int value1, T &&...values){
    m_context.extendValues(
        name, 
        {CppType<ValueType::Integer>::type{value1}, CppType<ValueType::Integer>::type{std::forward<T>(values)}...}
    );

    return *this;
}

template<typename... T>
inline CscEditor& CscEditor::extendValues(crString name, const char *value1, T &&...values){
    m_context.extendValues(
        name, 
        {CppType<ValueType::String>::type{value1}, CppType<ValueType::String>::type{std::forward<T>(values)}...}
    );

    return *this;
}


CSC_END
#endif