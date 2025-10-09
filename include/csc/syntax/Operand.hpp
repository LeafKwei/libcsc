#ifndef CSC_OPERAND_HPP
#define CSC_OPERAND_HPP

#include "csc/csc.hpp"
#include "csc/lex/types.hpp"
#include "csc/context/types.hpp"
#include "csc/syntax/types.hpp"
CSC_BEGIN

class Operand{
public:
    using crToken = const Token&;

public:
    Operand(const Token &token);

    crString           str() const noexcept;                     //获取token的str字段
    crToken           token() const noexcept;                //获取token
    TokenType      typeofToken() const noexcept;      //获取token类型
    OperandType typeofOperand() const noexcept;  //获取从token转换得到的OperandType类型
    ValueType       typeofValue() const noexcept;       //获取从token转换得到的ValueType类型
    Value              value() const;                                //将当前Operand转换为Value
    Value              zero() const;                                  //获取ValueType对应类型的零值
    static Value    zero(ValueType type);                    //获取给定的ValueType对应类型的零值

private:
    Token               m_token;
    OperandType   m_optype;
    ValueType        m_valtype;

    void                updateOperandType();
    void                updateValueType();
    ValueType       getValueTypeof(const Token &token);
    ValueType       getArrayValueTypeof(const Token &token);
    OperandType getOperandTypeof(const Token &token, ValueType type);
    OperandType getOtherOperandTypeof(const Token &token);
};

CSC_END
#endif