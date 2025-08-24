#ifndef CSC_CONTEXT_TYPES_HPP
#define CSC_CONTEXT_TYPES_HPP

#include <any>
#include <map>
#include <vector>
#include <memory>
#include "csc/csc.hpp"
#include "csc/alias.hpp"
CSC_BEGIN

struct Variable;
struct Scope;
using VariablePtr = std::shared_ptr<Variable>;
using ScopePtr = std::shared_ptr<Scope>;
using ScopeWkr = std::weak_ptr<Scope>;
using VariableKeeper = std::map<CscStr, VariablePtr>;
using ScopeKeeper = std::map<CscStr, ScopePtr>;
using ValueKeeper = std::vector<CscStr>;

enum class ValueType{
    Unknown, 
    Bool, Integer, Double, String,
    Bools, Integers, Doubles, Strings
};

struct Variable{
    CscStr name;
    ValueKeeper values;
    ValueType type;
};

struct Scope{
    CscStr name;
    ScopeWkr parent;
    VariableKeeper variables;
    ScopeKeeper scopes;
};

CSC_END
#endif