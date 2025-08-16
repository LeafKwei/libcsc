#ifndef DBC_TYPES_HPP
#define DBC_TYPES_HPP

#include <stdexcept>
#include "dbc/dbc.hpp"
#include "dbc/alias.hpp"
DBC_BEGIN

class Dexcept : public std::logic_error{
public:
    Dexcept(const std::string &msg) : logic_error(msg){}
};

class ContextExcept : public Dexcept{
public:
    ContextExcept(const std::string &msg) : Dexcept(msg){}
};

class CommandExcept : public Dexcept{
public:
    CommandExcept(const std::string &msg) : Dexcept(msg){}
};

DBC_END
#endif