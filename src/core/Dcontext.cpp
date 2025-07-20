#include <algorithm>
#include "dbc/core/Dcontext.hpp"
#include "dbc/utility/utility.hpp"

DBC_BEGIN

//=============== Constructor ===============
Dcontext::Dcontext(){
    m_rootPtr = std::make_shared<Ddomain>();
    m_rootPtr -> prev = m_rootPtr;
    m_rootPtr -> name = "/";
    m_currentPtr = m_rootPtr;
}

Dcontext::Dcontext(const Dcontext &oth){

}

Dcontext::Dcontext(Dcontext &&oth){

}

Dcontext::~Dcontext(){

}

//=============== Operator ===============
Dcontext& Dcontext::operator=(const Dcontext &oth){

}

Dcontext& Dcontext::operator=(Dcontext &&oth){

}

//=============== Public ===============
 bool Dcontext::existsDomain(const Dstring &path) const noexcept{
    if(isEmptyPath(path)) return false;
    return findDomain(path) != nullptr;
 }

Derror Dcontext::enterDomain(const Dstring &path) noexcept{
    if(isEmptyPath(path)) return Derror{ErrorType::Unexcepted, "Empty path."};

    DdomainPtr ptr = findDomain(path);
    if(ptr != nullptr){
        m_currentPtr = ptr;
        return Derror{ErrorType::OK};
    }

    return Derror{ErrorType::NoSuch, "No such domain."};
}

Derror Dcontext::makeDomain(const Dstring &path) noexcept{
    if(isEmptyPath(path)) return Derror{ErrorType::Unexcepted, "Empty path."};

    auto [prefix, name] = separate(path);
    auto backup = m_currentPtr;

    if(prefix.size() != 0){
        if(enterDomain(prefix).type != ErrorType::OK){
            return Derror{ErrorType::NoSuch, "No such path."};
        }
    }

    //>>>>>>>>>>>>>>>>>>>>>>>>>> >>>>>>
    /* Let we trusts user. OwO
    if(findDomain(name) != nullptr){                                       //If you try to make a repeated domain.
        return Derror{ErrorType::Denied, "Domain exists."};
    }
    */
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

    auto &head = m_currentPtr -> child;
    auto newDomain = std::make_shared<Ddomain>();
    newDomain -> name = name;
    newDomain -> parent = m_currentPtr;
    
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

    m_currentPtr = backup;
    return Derror{ErrorType::OK};
}

Derror Dcontext::makeDomains(const Dstring &path) noexcept{
    if(isEmptyPath(path)) return Derror{ErrorType::Unexcepted, "Empty path."};

    auto backup = m_currentPtr;
    auto names = splitPath(path);

    for(auto &name : names){
        auto err = enterDomain(name);
        if(err.type == ErrorType::NoSuch){
            makeDomain(name);
            enterDomain(name);
        }
    }

    m_currentPtr = backup;
    return Derror{ErrorType::OK};
}

Derror Dcontext::dropDomain(const Dstring &path) noexcept{
    if(isEmptyPath(path)) return Derror{ErrorType::Unexcepted, "Empty path."};

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
        assignDomainPrev(head, domain -> prev);
    }
    else{
        auto &before = domain -> prev;
        auto &after = domain -> next;
        before -> next = after;
        assignDomainPrev(after, before);
    }

    m_currentPtr = parent;           /* back to parent domain. */
    return Derror{ErrorType::OK};
}

Derror Dcontext::exitDomain() noexcept{
    if(m_currentPtr -> parent == nullptr) return Derror{ErrorType::Denied, "Root reached."};
    m_currentPtr = m_currentPtr -> parent;
    return Derror{ErrorType::OK};
}

Dstring Dcontext::path() const noexcept{
    return m_currentPtr -> name;
}

Dstring Dcontext::absolutePath() const noexcept{
    std::vector<Dstring> names;

    auto domain = m_currentPtr;
    while(domain != nullptr){
        names.push_back(domain -> name);
        domain = domain -> parent;
    }

    std::reverse(names.begin(), names.end());
    return join("/", names, {"/"});    
}

bool Dcontext::exists(const Dstring &name) const noexcept{
    return findPair(name) != nullptr;
}

void Dcontext::set(const Dstring &name, const Dstring &value) noexcept{
    auto pair = findPair(name);
    if(pair != nullptr){
        pair -> value = value;
        return;
    }

    auto newPair = std::make_shared<Dpair>();
    newPair -> name = name;
    newPair -> value = value;

    if(m_currentPtr -> pairs != nullptr){
        auto tail = m_currentPtr -> pairs -> prev;
        tail -> next = newPair;
        newPair -> prev = tail;
        return;
    }

    m_currentPtr -> pairs = newPair;
    newPair -> prev = newPair;
}

void Dcontext::unset(const Dstring &name) noexcept{
    auto pair = findPair(name);
    if(pair == nullptr){
        return;
    }

    auto &head = m_currentPtr -> pairs;

    if(head == pair){
        head = pair -> next;
        assignPairPrev(head, pair -> prev);
    }
    else{
        auto &before = pair -> prev;
        auto &after = pair -> next;

        before -> next = after;
        assignPairPrev(after, before);
    }
}

Dstring Dcontext::get(const Dstring &name) noexcept{
    auto pair = findPair(name);
    if(pair != nullptr){
        return pair -> value;
    }

    return Dstring("");
}

//=============== Private ===============

inline void Dcontext::assignPairPrev(DpairPtr &lhs, DpairPtr &rhs){
    if(lhs != nullptr){
        lhs -> prev = rhs -> prev;
    }
}

inline void Dcontext::assignDomainPrev(DdomainPtr &lhs, DdomainPtr &rhs) const noexcept{
    if(lhs != nullptr){
        lhs -> prev = rhs;
    }
}

DpairPtr Dcontext::findPair(const Dstring &name) const noexcept{
    auto nextptr = m_currentPtr -> pairs;

    while(nextptr != nullptr){
        if(nextptr -> name == name){
            return nextptr;
        }

        nextptr = nextptr -> next;
    }

    return DpairPtr(nullptr);
}

DdomainPtr Dcontext::findDomain(const Dstring &path) const noexcept{
    auto names = splitPath(path);

    if(names.at(0) == "/"){
        if(names.size() == 1) return m_rootPtr;              /* 'names' contains '/' only. */
        return findDomainFrom(m_rootPtr -> child, names, 1);
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