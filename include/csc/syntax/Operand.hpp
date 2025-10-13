#ifndef CSC_OPERAND_HPP
#define CSC_OPERAND_HPP

#include "csc/csc.hpp"
#include "csc/lex/types.hpp"
#include "csc/context/types.hpp"
#include "csc/context/ValueMaker.hpp"
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
    Value               value() const;                                 //将当前Operand转换为Value
    String               key() const;                                    //获取Operand对应的key，key将用于CmdExecutor的命令查找

private:
    Token               m_token;
    OperandType   m_type;
    ValueMaker      m_maker;

    void                updateOperandType();
    OperandType getOperandTypeof(const Token &token) const;
};

CSC_END
#endif