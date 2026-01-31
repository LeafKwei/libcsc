#include "csc/types.hpp"
#include "csc/context/val.hpp"
#include "csc/context/Querier.hpp"
CSC_BEGIN

Querier::Querier(VariablePtr varp) : var_(varp){

}

ValueType Querier::queryType() const{
    auto varptr = lockVariablePtr();
    return varptr -> type;
}

Size_t Querier::querySize() const{
    auto varptr = lockVariablePtr();
    return varptr -> values.size();
}

Value Querier::queryValue(int index) const{
    auto varptr = lockVariablePtr();

    /* 如果index在values的大小之内，返回对应位置的值，否则返回一个零值 */
    auto uindex = static_cast<Size_t>(index);
    return (uindex < varptr -> values.size()) 
        ? varptr -> values.at(index)
        : makeZeroValue(varptr -> type);
}

VariablePtr Querier::lockVariablePtr() const{
    if(var_.expired()){
        throw ContextExcept("Variable weakptr has expired.");
    }

    return var_.lock();
}

CSC_END