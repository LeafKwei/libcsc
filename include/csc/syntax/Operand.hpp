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
    using ValueUnitList = std::vector<ValueUnit>;
    using ValueUnitCR  = const ValueUnit &;
    using Type              = OperandType;

public:
    Operand(TokenHolder &holder);

    String key() const noexcept;      /* 获取此操作数生成的key */
    Type   type() const noexcept;    /* 获取此操作数的类型 */
    Size_t size() const noexcept;     /* 获取此操作数中的值的数量 */
    String           stringvalue(int index=0) const; /* 获取指定位置的值并转换为字符串(该值必须是ValueType::String类型) */
    ValueUnit     value(int index=0) const;          /* 获取指定位置的值及其类型组成的ValueUnit */
    ValueUnitCR refervalue(int index=0) const;  /* 获取指定位置的值及其类型组成的ValueUnit的const引用 */

private:
    String                key_;
    OperandType    type_;
    ValueUnitList     valueunits_;

    void initOperand(TokenHolder &holder);
    void initValue(TokenHolder &holder);
    void initValidValue(TokenHolder &holder);
    void initNonValidValue(TokenHolder&holder);
    void initType(TokenHolder &holder);
    void initKey(TokenHolder &holder);
};

CSC_END
#endif