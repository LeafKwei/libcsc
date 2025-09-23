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

CSC_END
#endif