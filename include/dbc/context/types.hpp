#ifndef DBC_CONTEXT_TYPES_HPP
#define DBC_CONTEXT_TYPES_HPP

#include <map>
#include <memory>
#include "dbc/dbc.hpp"
#include "dbc/alias.hpp"
DBC_BEGIN

struct Variable;
struct Scope;
using VariablePtr = std::shared_ptr<Variable>;
using ScopePtr = std::shared_ptr<Scope>;
using ScopeWkr = std::weak_ptr<Scope>;
using VariableKeeper = std::map<Dstring, VariablePtr>;
using ScopeKeeper = std::map<Dstring, ScopePtr>;

enum class ValueType{
    Unknown, 
    Bool, Integer, Double, String,
    Bools, Integers, Doubles, Strings
};

struct Variable{
    ValueType type;
    Dstring name;
    Dstring value;
};

struct Scope{
    Dstring name;
    ScopeWkr parent;
    VariableKeeper variables;
    ScopeKeeper scopes;
};

DBC_END
#endif