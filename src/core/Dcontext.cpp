#include "dbc/core/Dcontext.hpp"

DBC_BEGIN

//=============== Constructor ===============
Dcontext::Dcontext(){
    m_rootPtr = std::make_shared<Ddomain>();
    m_rootPtr -> prev = m_rootPtr;
    m_rootPtr -> name = "/";
    m_currentPtr = m_rootPtr;
}

//=============== Public ===============
 bool Dcontext::existsDomain(const Dstring &path) const noexcept{
    return findDomain(path) != nullptr;
 }

Derror Dcontext::enterDomain(const Dstring &path) noexcept{
    DdomainPtr ptr = findDomain(path);
    if(ptr != nullptr){
        m_currentPtr = ptr;
        return Derror{ErrorType::OK};
    }

    return Derror{ErrorType::NoSuch, "No such domain."};
}
    
Derror Dcontext::makeDomain(const Dstring &path) noexcept{
    auto [prefix, name] = separate(path);

    if(prefix.size() != 0){
        if(enterDomain(prefix).type != ErrorType::OK){
            return Derror{ErrorType::NoSuch, "No such path."};
        }
    }

    auto &head = m_currentPtr -> child;
    auto newDomain = std::make_shared<Ddomain>();
    newDomain -> name = name;
    
    if(head == nullptr){  /* If current domain has no child yet. */
        head = newDomain; 
        head -> prev = newDomain;
    }
    else{
        auto &tail = head -> prev;
        tail -> next = newDomain;     /* tail0 -> tail1 */
        newDomain -> prev = tail;     /* tail0 <- tail1 */
        head -> prev = newDomain; /* <- head ... tailn <- */
    }

    return Derror{ErrorType::OK};
}

Derror Dcontext::dropDomain(const Dstring &path) noexcept{
    auto domain = findDomain(path);
    if(domain == nullptr){
        return Derror{ErrorType::NoSuch, "No such path."};
    }

    auto parent = domain -> parent;
    if(parent == nullptr){
        return Derror{ErrorType::Denied, "Can't drop root domain."};
    }

    auto &head = parent -> child;

    if(head == domain){  /* If 'domain' is the head of child list. */
        head = domain -> next;
        assignPrev(head, domain -> prev);
    }
    else{
        auto &before = domain -> prev;
        auto &after = domain -> next;
        before -> next = after;
        assignPrev(after, before);
    }

    return Derror{ErrorType::OK};
}

Derror Dcontext::exitDomain() noexcept{
    if(m_currentPtr -> parent == nullptr) return Derror{ErrorType::Denied, "Root reached."};
    m_currentPtr = m_currentPtr -> parent;
    return Derror{ErrorType::OK};
}

bool Dcontext::exists(const Dstring &name) const noexcept{

}

void Dcontext::set(const Dstring &name, const Dstring &value) noexcept{

}

void Dcontext::unset(const Dstring &name) noexcept{

}

Dstring Dcontext::get(const Dstring &name) noexcept{

}

//=============== Private ===============

inline void Dcontext::assignPrev(DdomainPtr &lhs, DdomainPtr &rhs) const noexcept{
    if(lhs != nullptr){
        lhs -> prev = rhs;
    }
}

std::tuple<Dstring,Dstring> Dcontext::separate(const Dstring &path) const noexcept{
    Dstring prefix;
    Dstring name;

    auto pos = path.find_last_of('/');
    if(pos >= path.size()){
        name = path;
        return std::make_tuple(prefix, name);
    }

    prefix = path.substr(0, pos);
    return std::make_tuple(prefix, name);
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

DdomainPtr Dcontext::findDomain(const Dstring &path) const noexcept{
    std::vector<Dstring> names = splitPath(path);

    if(names.at(0) == "/"){
        if(names.size() == 1) return m_rootPtr;              /* 'names' contains '/' only. */
        return findDomainFrom(m_rootPtr -> child, names, 0);
    }
    else{
        return findDomainFrom(m_currentPtr -> child, names, 0);
    }
}

DdomainPtr Dcontext::findDomainFrom(DdomainPtr begin, const std::vector<Dstring> &names, std::size_t pos) const noexcept{
    auto nextptr = begin;

    if(pos < names.size()){
        while(nextptr != nullptr){
            if(nextptr -> name == names.at(pos)){
                if(pos + 1 == names.size()) return nextptr;
                return findDomainFrom(nextptr -> child, names, pos + 1);
            }

            nextptr = nextptr -> next;
        }
    }

    return DdomainPtr(nullptr);
}

    DBC_END