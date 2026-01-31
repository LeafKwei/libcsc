#include "csc/types.hpp"
#include "csc/context/val.hpp"
#include "csc/context/Querier.hpp"
CSC_BEGIN

Querier::Querier(VariablePtr varp) : var_(varp){

}

String Querier::name() const{
    return lockVariablePtr() -> name;
}

ValueType Querier::type() const{
    return lockVariablePtr() -> type;
}

Size_t Querier::size() const{
    return lockVariablePtr() -> values.size();
}

Value Querier::value(int index) const{
    auto varptr = lockVariablePtr();

    /* 如果index在values的大小之内，返回对应位置的值，否则返回一个零值 */
    auto uindex = static_cast<Size_t>(index);
    return (uindex < varptr -> values.size()) 
        ? varptr -> values.at(index)
        : makeZeroValue(varptr -> type);
}

ValueUnit Querier::valueunit(int index) const{
    auto varptr = lockVariablePtr();
    
    auto uindex = static_cast<Size_t>(index);
    return (uindex < varptr -> values.size()) 
        ? ValueUnit{varptr -> values.at(index), varptr -> type}
        : ValueUnit{makeZeroValue(varptr -> type), varptr -> type};
}

VariablePtr Querier::lockVariablePtr() const{
    if(var_.expired()){
        throw ContextExcept("Variable weakptr has expired.");
    }

    return var_.lock();
}

CSC_END