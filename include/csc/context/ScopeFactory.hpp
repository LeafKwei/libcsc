#ifndef CSC_SCOPEFACTORY_HPP
#define CSC_SCOPEFACTORY_HPP

#include "csc/context/impl/MapScope.hpp"
#include "csc/context/impl/ListScope.hpp"
CSC_BEGIN

template<typename... T>
inline ScopePtr factory_makeSharedScope(ScopeType type, T &&...args){
    switch(type){
        case ScopeType::MapScope:
            return std::make_shared<MapScope>(args...);
        case ScopeType::ListScope:
            return std::make_shared<ListScope>(args...);
        default:
            return nullptr;
    }
}

CSC_END
#endif