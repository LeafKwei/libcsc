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
    using Holder = TokenHolder;
    using Type    = OperandType;

public:
    Operand(const TokenHolder &holder);
    Operand(TokenHolder &&holder);

    Holder& holder();
    String     key() const noexcept;
    Type       type() const noexcept;

private:
    String                key_;
    TokenHolder     holder_;
    OperandType    type_;

    void initOperand();
    void initType();
    void initKey();
};

CSC_END
#endif