#ifndef DBC_SEEKER_HPP
#define DBC_SEEKER_HPP

#include "dbc/dbc.hpp"
#include "dbc/alias.hpp"
DBC_BEGIN

template<typename Rt>
class Dseeker{
public:
    virtual Rt result() const =0;
};

DBC_END
#endif