#ifndef CSC_OPERAND_HPP
#define CSC_OPERAND_HPP

#include "csc/csc.hpp"
#include "csc/lex/TokenHolder.hpp"
#include "csc/context/types.hpp"
#include "csc/context/val.hpp"
#include "csc/syntax/types.hpp"
CSC_BEGIN

class Operand{
public:

public:
    Operand(const TokenHolder &holder);
    Operand(TokenHolder &&holder);

    const Token& token() const;                                 //获取token
    const Token& token(int index) const;                  //获取指定位置的token
    TokenType      tokenType() const noexcept;         //获取token类型
    TokenType      tokenType(int index) const;          //获取指定位置的token类型
    Size_t              tokenSize() const noexcept;         //获取总token数量
    OperandType operandType() const noexcept;     //获取OperandType类型
    String              key() const;                                    //获取Operand对应的key，key将用于CmdExecutor的命令查找

private:
    TokenHolder     holder_;
    OperandType    type_;
    
    void                updateOperandType();
    OperandType getOperandTypeof(const Token &token) const;
};

CSC_END
#endif