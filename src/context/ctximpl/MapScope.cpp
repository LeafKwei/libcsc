#include "csc/context/ctximpl/MapScope.hpp"
CSC_BEGIN

MapScope::MapScope(const String &name, UID id) : name_(name), id_(id){

}

bool MapScope::insertVariable(const String &name, VariablePtr vp){
    return variables_.insert({name, vp}).second;
}

VariablePtr MapScope::findVariable(const String &name){
    auto pos = variables_.find(name);
    if(pos == variables_.end()){
        return nullptr;
    }

    return pos -> second;
}

VariablePtr MapScope::variable(int index){
    auto pos = std::next(variables_.begin(), index);
    if(pos == std::end(variables_)){
        return nullptr;
    }

    return pos -> second;
}

Size_t MapScope::size() const noexcept{

}

String MapScope::name() const noexcept{

}

UID MapScope::id() const noexcept{

}

CSC_END