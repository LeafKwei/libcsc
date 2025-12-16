#ifndef CSC_VALUEACCESSOR_HPP
#define CSC_VALUEACCESSOR_HPP

#include <vector>
#include "csc/csc.hpp"
#include "csc/alias.hpp"
#include "csc/context/types.hpp"
#include "csc/context/valtool.hpp"
CSC_BEGIN

/* ValueAccessor是对ValueKeeper的包装，对外提供多变量值的访问功能 */
class ValueAccessor{
public:
    ValueAccessor(const ValueKeeper &keeper, ValueType type) : keeper_(keeper), type_(type){}
    ValueType type() const        { return type_; }
    bool          isEmpty() const  { return keeper_.empty(); }
    Size_t        size() const         { return keeper_.size(); }
    Value        value() const       { return (keeper_.size() > 0) ?  keeper_.at(0) :  makeZeroValue(type_);}
    Value        value(int index) const          { return keeper_.at(index); }
    Value        operator[] (int index) const { return keeper_[index]; }

private:
    const ValueKeeper &keeper_;
    ValueType                 type_;
};

CSC_END
#endif