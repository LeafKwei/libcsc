#ifndef CSC_EDITOR_HPP
#define CSC_EDITOR_HPP

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

    template<typename T>
    CscEditor& makeVariable(crString name, std::initializer_list<T> values, ValueType type);
    template<typename T>
    CscEditor& extendValues(crString name, std::initializer_list<T> values);
    CscEditor& cleanVariable(crString name);

private:
    bool m_autoEnter;
    Context &m_context;
};

/**
 * What can I say.
 * 项目写到最后才发现用std::any会导致int和const char*没法隐式转换到long和std::string，所以只能将CscEditor内的这两个函数
 * 改成模板，然后通过模板特例化对int和const char*进行特殊处理。
 */
template<typename T>
inline CscEditor& CscEditor::extendValues(crString name, std::initializer_list<T> values){
    for(auto &v : values){
        m_context.extendValues(name, {v});
    }
    return *this;
}

template<>
inline CscEditor& CscEditor::extendValues<int>(crString name, std::initializer_list<int> values){
    for(auto &v : values){
        m_context.extendValues(name, {CppType<ValueType::Integer>::type{v}});
    }
    return *this;
}

template<>
inline CscEditor& CscEditor::extendValues<const char*>(crString name, std::initializer_list<const char*> values){
    for(auto &v : values){
        m_context.extendValues(name, {CppType<ValueType::String>::type{v}});
    }
    return *this;
}

template<typename T>
inline CscEditor& CscEditor::makeVariable(crString name, std::initializer_list<T> values, ValueType type){
    m_context.makeVariable(name, {}, type);
    return extendValues(name, values);
}

template<>
inline CscEditor& CscEditor::makeVariable<int>(crString name, std::initializer_list<int> values, ValueType type){
    m_context.makeVariable(name, {}, type);
    return extendValues(name, values);
}

template<>
inline CscEditor& CscEditor::makeVariable<const char*>(crString name, std::initializer_list<const char*> values, ValueType type){
    m_context.makeVariable(name, {}, type);
    return extendValues(name, values);
}

CSC_END
#endif