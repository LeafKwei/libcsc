#ifndef CSC_TYPES_HPP
#define CSC_TYPES_HPP

#include <stdexcept>
#include "csc/csc.hpp"
#include "csc/alias.hpp"
CSC_BEGIN

/* 对异常的通用的类型进行声明定义 */

class CscExcept : public std::logic_error{
public:
    CscExcept(const std::string &msg) : logic_error(msg){}
};

class LexExcept : public CscExcept{
public:
    LexExcept(const std::string &msg) : CscExcept(msg){}
};

class ContextExcept : public CscExcept{
public:
    ContextExcept(const std::string &msg) : CscExcept(msg){}
};

class CommandExcept : public CscExcept{
public:
    CommandExcept(const std::string &msg) : CscExcept(msg){}
};

class ActionExcept : public CscExcept{
public:
    ActionExcept(const std::string &msg) : CscExcept(msg){}
};

/* 对关键字进行声明 */
extern const String KW_TRUE;        //true和false会在syntax和context被当作OperandType::Value或ValueType::Bool类型处理
extern const String KW_FALSE;
extern const String KW_ACTION;

CSC_END
#endif