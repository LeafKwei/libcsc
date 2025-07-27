#ifndef DBC_CHARPICKER_HPP
#define DBC_CHARPICKER_HPP

#include "dbc/dbc.hpp"
#include "dbc/alias.hpp"
#include "dbc/lex/CharsOptor.hpp"
DBC_BEGIN

// Note: For compliing error 'undefined reference to vtable for XXX', please check whether there is non-virtual funcion unimplementing.
class CharPicker{
public:
    virtual Dchar pick() noexcept =0;
    virtual Dchar tryPick() const noexcept =0;                             //Pick char but don't increase index.
    virtual void forward(unsigned int value=1) noexcept =0;     //Increase index.
    virtual void backward(unsigned int value=1) noexcept =0;  //Decrease index.
    virtual bool hasMore() const noexcept =0;
    virtual int count() noexcept =0;                                             //Get count of picking from last calling count().
    virtual CharsOptor charsoptor() const noexcept =0;            //Get a operator which can be used to do operations for a string. 
};

DBC_END
#endif