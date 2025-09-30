#ifndef CSC_VALUES_HPP
#define CSC_VALUES_HPP

#include <cassert>
#include <vector>
#include "csc/csc.hpp"
#include "csc/alias.hpp"
#include "csc/context/types.hpp"
CSC_BEGIN

class VariableValues{
public:
    VariableValues(const ValueKeeper &keeper, ValueType type) : m_keeper(keeper), m_type(type){}
    ValueType type() const        { return m_type; }
    bool          isEmpty() const  { return m_keeper.empty(); }
    Size_t        size() const         { return m_keeper.size(); }
    Value        val() const           { assert(m_keeper.size() > 0); return m_keeper.at(0); }
    Value        val(int index) const              { return m_keeper.at(index); }
    Value        operator[] (int index) const { return m_keeper[index]; }

private:
    const ValueKeeper &m_keeper;
    ValueType m_type;
};

CSC_END
#endif