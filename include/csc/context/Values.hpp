#ifndef CSC_VALUES_HPP
#define CSC_VALUES_HPP

#include <cassert>
#include <vector>
#include "csc/csc.hpp"
#include "csc/alias.hpp"
#include "csc/context/types.hpp"
CSC_BEGIN

class Values{
public:
    Values(const ValueKeeper &keeper, ValueType type) : m_keeper(keeper), m_type(type){}
    ValueType type() const      { return m_type; }
    bool          isEmpty() const { return m_keeper.empty(); }
    int             size() const       { return m_keeper.size(); }
    CscStr       value() const     { assert(m_keeper.size() > 0); return m_keeper.at(0); }
    CscStr       value(int index) const          { return m_keeper.at(index); }
    CscStr       operator[] (int index) const { return m_keeper[index]; }

private:
    const ValueKeeper &m_keeper;
    ValueType m_type;
};

CSC_END
#endif