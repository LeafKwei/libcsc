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
    using InitValues = std::initializer_list<String>;

public:
    CscEditor(Context &context);

    CscEditor& autoEnterOn();                  /* 启用自动进入作用域的功能，当makeScope函数创建作用域后，自动进入该作用域 */
    CscEditor& autoEnterOff();                  /* 禁用自动进入作用域的功能(默认) */
    CscEditor& makeScope(crString name);
    CscEditor& enterScope(crString name);
    CscEditor& leaveScope();
    CscEditor& cleanScope(crString name);
    CscEditor& makeVariable(crString name, InitValues values, ValueType type);
    CscEditor& extendValues(crString name, InitValues values);
    CscEditor& cleanVariable(crString name);

private:
    bool m_autoEnter;
    Context &m_context;
};

CSC_END
#endif