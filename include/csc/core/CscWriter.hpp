#ifndef CSC_WRITER_HPP
#define CSC_WRITER_HPP

#include <utility>
#include "csc/context/Context.hpp"
CSC_BEGIN

 /**
  * CscWriter是对Context的封装，旨在向用户提供更精简的操作Context的功能，用户可通过使用CscWriter来编辑Context中的内容，
  * 由此来改变通过CscHandler::toString函数产生的csc配置文件的内容。
  */
class CscWriter{
public:
    CscWriter(Context &context);

    CscWriter& autoEnterOn();                  /* 启用自动进入作用域的功能，当makeScope函数创建作用域后，自动进入该作用域 */
    CscWriter& autoEnterOff();                  /* 禁用自动进入作用域的功能(默认) */
    CscWriter& makeScope(const String &name);
    CscWriter& enterScope(const String &name);
    CscWriter& leaveScope();
    CscWriter& cleanScope(const String &name);

    template<typename... T>
    CscWriter& makeVariable(const String &name, ValueType type, T &&...values);
    template<typename... T>
    CscWriter& makeVariable(const String &name, ValueType type, int value1, T &&...values);                //通过重载函数模板并将value1指定为int，从而让编译器优先选择此版本处理int类型的数据
    template<typename... T>
    CscWriter& makeVariable(const String &name, ValueType type, const char *value1, T &&...values);  //通过重载函数模板并将value1指定为const char*，从而让编译器优先选择此版本处理char*类型的数据
    template<typename... T>
    CscWriter& extendValues(const String &name, T &&...values);
    template<typename... T>
    CscWriter& extendValues(const String &name, int value1, T &&...values);
    template<typename... T>
    CscWriter& extendValues(const String &name, const char *value1, T &&...values);

    CscWriter& cleanVariable(const String &name);

private:
    bool autoEnter_;
    Context &context_;
};

template<typename... T>
inline CscWriter& CscWriter::makeVariable(const String &name, ValueType type, T &&...values){
    context_.makeVariable(name, type, {std::forward<T>(values)...});
    return *this;
}

template<typename... T>
inline CscWriter& CscWriter::makeVariable(const String &name, ValueType type, int value1, T &&...values){
    context_.makeVariable(
        name, 
        type,
        {CppType<ValueType::Integer>::type{value1}, CppType<ValueType::Integer>::type{std::forward<T>(values)}...}
    );

    return *this;
}

template<typename... T>
inline CscWriter& CscWriter::makeVariable(const String &name, ValueType type, const char *value1, T &&...values){
    context_.makeVariable(
        name, 
        type,
        {CppType<ValueType::String>::type{value1}, CppType<ValueType::String>::type{std::forward<T>(values)}...}
    );

    return *this;
}

template<typename... T>
inline CscWriter& CscWriter::extendValues(const String &name, T &&...values){
    context_.extendValues(name, {std::forward<T>(values)...});
    return *this;
}

template<typename... T>
inline CscWriter& CscWriter::extendValues(const String &name, int value1, T &&...values){
    context_.extendValues(
        name, 
        {CppType<ValueType::Integer>::type{value1}, CppType<ValueType::Integer>::type{std::forward<T>(values)}...}
    );

    return *this;
}

template<typename... T>
inline CscWriter& CscWriter::extendValues(const String &name, const char *value1, T &&...values){
    context_.extendValues(
        name, 
        {CppType<ValueType::String>::type{value1}, CppType<ValueType::String>::type{std::forward<T>(values)}...}
    );

    return *this;
}


CSC_END
#endif