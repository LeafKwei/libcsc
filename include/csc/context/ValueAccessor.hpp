#ifndef CSC_VALUEACCESSOR_HPP
#define CSC_VALUEACCESSOR_HPP

#include <vector>
#include "csc/csc.hpp"
#include "csc/alias.hpp"
#include "csc/context/types.hpp"
#include "csc/context/ValueMaker.hpp"
CSC_BEGIN

/* ValueAccessor是对ValueKeeper的包装，对外提供多变量值的访问功能 */
class ValueAccessor{
public:
    ValueAccessor(const ValueKeeper &keeper, ValueType type) : m_keeper(keeper), m_type(type){}
    ValueType type() const        { return m_type; }
    bool          isEmpty() const  { return m_keeper.empty(); }
    Size_t        size() const         { return m_keeper.size(); }
    Value        value() const       { return (m_keeper.size() > 0) ?  m_keeper.at(0) :  ValueMaker::makeZero(m_type);}
    Value        value(int index) const          { return m_keeper.at(index); }
    Value        operator[] (int index) const { return m_keeper[index]; }

private:
    const ValueKeeper &m_keeper;
    ValueType                 m_type;
};

CSC_END
#endif