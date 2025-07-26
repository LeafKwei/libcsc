#ifndef DBC_CHARPICKER_HPP
#define DBC_CHARPICKER_HPP

#include "dbc/dbc.hpp"
#include "dbc/alias.hpp"
DBC_BEGIN

class CharPicker{
public:
    virtual Dchar pick() noexcept =0;
    virtual Dchar tryPick() noexcept =0;                       //Pick char but don't increase index.
    virtual void forward(int value=1) noexcept =0;     //Increase index.
    virtual void backward(int value=1) noexcept =0;  //Decrease index.
    virtual bool hasMore() const noexcept =0;
    virtual void setIndexFlag(bool flag) noexcept =0;   //true: increase flag after picking char, otherwise not.
};

DBC_END
#endif