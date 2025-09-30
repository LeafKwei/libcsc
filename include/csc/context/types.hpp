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
using Value = std::any;
using crValue = const Value&;
using VariablePtr = std::shared_ptr<Variable>;
using ScopePtr = std::shared_ptr<Scope>;
using ScopeWkr = std::weak_ptr<Scope>;
using VariableKeeper = std::map<String, VariablePtr>;
using ScopeKeeper = std::map<String, ScopePtr>;
using ValueKeeper = std::vector<Value>;

enum class ValueType{
    Unknown, 
    Bool, Integer, Double, String,        //bool、int/long、double、std::string
    Bools, Integers, Doubles, Strings  //std::vector<bool>...
};

struct Variable{
    String name;
    ValueKeeper values;
    ValueType type;
};

struct ScopePos{
    ScopeWkr scope;
};

struct ScopeMetaData{
    UID id;
    String name;
    ScopeWkr ptr;
};

struct Scope{
    ScopeMetaData meta;
    ScopeWkr          parent;
    VariableKeeper  variables;
    ScopeKeeper     scopes;
};

struct VariableValue{
    Value value;
    ValueType type;
};

CSC_END
#endif