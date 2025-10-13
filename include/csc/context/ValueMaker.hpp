#ifndef CSC_VALUEMAKER_HPP
#define CSC_VALUEMAKER_HPP

#include "csc/lex/types.hpp"
#include "csc/context/types.hpp"
CSC_BEGIN

class ValueMaker{
public:
    ValueMaker(const Token &token);
    ValueType type() const noexcept;           //获取值的类型
    Value         value() const noexcept;         //获取值
    Value         make(const Token &token);  //使用给定的token生成值，同时更新自身

public:
    static Value makeZero(ValueType type); //生成给定ValueType枚举对应CppType的零值

private:
    ValueUnit m_unit;

    Value         getValueof(const Token &token);
    ValueType getValueTypeof(const Token &token) const;
    ValueType getArrayValueTypeof(const Token &token) const;
};

CSC_END
#endif