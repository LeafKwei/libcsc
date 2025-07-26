#ifndef DBC_CHARPICKER_HPP
#define DBC_CHARPICKER_HPP

#include "dbc/dbc.hpp"
#include "dbc/alias.hpp"
DBC_BEGIN

class CharPicker{
public:
    virtual Dchar pick() noexcept =0;
    virtual Dstring pickn(unsigned int n) noexcept =0;                //Pick n char.
    virtual Dchar tryPick() const noexcept =0;                             //Pick char but don't increase index.
    virtual Dstring tryPickn(unsigned int n) const noexcept =0; //Pick n char but don't increase index.
    virtual void forward(unsigned int value=1) noexcept =0;     //Increase index.
    virtual void backward(unsigned int value=1) noexcept =0;  //Decrease index.
    virtual bool hasMore() const noexcept =0;
};

DBC_END
#endif