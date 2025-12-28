#ifndef CSC_SCOPEFACTORY_HPP
#define CSC_SCOPEFACTORY_HPP

#include <utility>
#include "csc/context/impl/MapScope.hpp"
#include "csc/context/impl/ListScope.hpp"
CSC_BEGIN

template<typename... T>
inline ScopePtr factory_makeSharedScope(ScopeType type, T &&...args){
    switch(type){
        case ScopeType::MapScope:
            return std::make_shared<MapScope>(std::forward(args)...);
        case ScopeType::ListScope:
            return std::make_shared<ListScope>(std::forward(args)...);
        default:
            return nullptr;
    }
}

CSC_END
#endif