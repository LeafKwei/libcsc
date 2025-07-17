#include "dbc/core/Dcontext.hpp"

DBC_BEGIN

using std::size_t;

Dcontext::Dcontext(){
    m_rootPtr = std::make_shared<Dscope>();
    m_rootPtr -> name = "/";
    m_currentPtr = m_rootPtr;
}

Dcontext::Dcontext(Dcontext &&oth){

}

Dcontext::~Dcontext(){

}

bool Dcontext::testScope(const Dstring &path) const noexcept{
    auto names = splitPath(path);

    if(names.size() == 0) return false;
    if(names.at(0) == "/"){
        return findScopeFromRoot(names) != nullptr;
    }

    return findScopeFromCurrent(names) != nullptr;
}

std::vector<Dstring> Dcontext::splitPath(const Dstring &path) const noexcept{
    std::vector<Dstring> names;
    decltype(path.size()) pos = 0;
    decltype(path.size()) size = path.size();
    
    while(pos < path.size()){
        auto nextPos = path.find('/', pos);
       
        if(nextPos == 0){
            names.push_back("/");
            pos = nextPos + 1;
        }
        else if(nextPos > 0 && nextPos < size){
            if(nextPos == pos){
                names.push_back("");
                pos = nextPos + 1;
            }
            else{
                names.push_back(path.substr(pos, nextPos - pos));
                pos = nextPos + 1;
            }
        }
        else{
            names.push_back(path.substr(pos));
            pos = size;
        }
    }

    return names;
}

DscopePtr Dcontext::findScopeFromRoot(const std::vector<Dstring> &names) const noexcept{
    if((names.size() == 1) && (m_rootPtr -> name == names.at(0))){
        return m_rootPtr;
    }

    return findScopeFrom(m_rootPtr -> child, names, 1);
}

DscopePtr Dcontext::findScopeFromCurrent(const std::vector<Dstring> &names) const noexcept{
    return findScopeFrom(m_currentPtr -> child, names, 0);
}

DscopePtr Dcontext::findScopeFrom(const DscopePtr &begin, const std::vector<Dstring> &names,  size_t pos) const noexcept{
    auto nextptr = begin;

    if(pos >= names.size()){
        return DscopePtr(nullptr);
    }

    while(nextptr != nullptr){
        if(nextptr -> name == names.at(pos)){
            if(pos + 1 == names.size()) return nextptr;
            return findScopeFrom(nextptr -> child, names, pos + 1);
        }

        nextptr = nextptr -> next;
    }

    return DscopePtr(nullptr);
}

DBC_END