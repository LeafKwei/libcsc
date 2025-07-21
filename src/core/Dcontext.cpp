#include <algorithm>
#include <cassert>
#include "dbc/core/Dcontext.hpp"
#include "dbc/utility/utility.hpp"

DBC_BEGIN

//=============== Constructor ===============
Dcontext::Dcontext(){
    m_rootPtr = std::make_shared<Ddomain>();
    m_rootPtr -> prev = m_rootPtr;
    m_rootPtr -> name = "/";
    m_crntPtr = m_rootPtr;
    m_lastPtr = m_rootPtr;
}

Dcontext::Dcontext(const Dcontext &oth){
    m_rootPtr = oth.m_rootPtr;
    m_crntPtr = oth.m_crntPtr;
    m_lastPtr = oth.m_lastPtr;
}

Dcontext::Dcontext(Dcontext &&oth) noexcept{
    m_rootPtr = oth.m_rootPtr;
    m_crntPtr = oth.m_crntPtr;
    m_lastPtr = oth.m_lastPtr;
    oth.m_rootPtr = nullptr;
    oth.m_crntPtr = nullptr;
    oth.m_lastPtr = nullptr;
}

Dcontext::~Dcontext(){

}

//=============== Operator ===============
Dcontext& Dcontext::operator=(const Dcontext &oth){
    assert(this != &oth);

    m_rootPtr = oth.m_rootPtr;
    m_crntPtr = oth.m_crntPtr;
    m_lastPtr = oth.m_lastPtr;
}

Dcontext& Dcontext::operator=(Dcontext &&oth) noexcept{
    assert(this != &oth);

    m_rootPtr = oth.m_rootPtr;
    m_crntPtr = oth.m_crntPtr;
    m_lastPtr = oth.m_lastPtr;
    oth.m_rootPtr = nullptr;
    oth.m_crntPtr = nullptr;
    oth.m_lastPtr = nullptr;
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
        m_lastPtr = m_crntPtr;
        m_crntPtr = ptr;
        return Derror{ErrorType::OK};
    }

    return Derror{ErrorType::NoSuch, "No such domain."};
}

Derror Dcontext::backDomain() noexcept{
    auto tmp = m_crntPtr;
    m_crntPtr = m_lastPtr;
    m_lastPtr = tmp;
}

Derror Dcontext::makeDomain(const Dstring &path) noexcept{
    if(isEmptyPath(path)) return Derror{ErrorType::Unexcepted, "Empty path."};

    auto [prefix, name] = separate(path);

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

    auto &head = m_crntPtr -> child;
    auto newDomain = std::make_shared<Ddomain>();
    newDomain -> name = name;
    newDomain -> parent = m_crntPtr;
    
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

    backDomain();
    return Derror{ErrorType::OK};
}

Derror Dcontext::makeDomains(const Dstring &path) noexcept{
    if(isEmptyPath(path)) return Derror{ErrorType::Unexcepted, "Empty path."};

    auto backup = m_crntPtr;
    auto names = splitPath(path);

    for(auto &name : names){
        auto err = enterDomain(name);
        if(err.type == ErrorType::NoSuch){
            makeDomain(name);
            enterDomain(name);
        }
    }

    m_crntPtr = backup;
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

    m_crntPtr = parent;           /* back to parent domain. */
    return Derror{ErrorType::OK};
}

Derror Dcontext::exitDomain() noexcept{
    if(m_crntPtr -> parent == nullptr) return Derror{ErrorType::Denied, "Root reached."};
    m_crntPtr = m_crntPtr -> parent;
    return Derror{ErrorType::OK};
}

Derror Dcontext::attachDomain(const Dstring &path, Dcontext &&context) noexcept{
    if(isEmptyPath(path)) return Derror{ErrorType::Unexcepted, "Empty path."};

    auto [prefix, name] = separate(path);
    if(prefix.size() != 0){
        if(enterDomain(prefix).type != ErrorType::OK){
            return Derror{ErrorType::NoSuch, "No such path."};
        }
    }

    

}

Dcontext Dcontext::detachDomain(const Dstring &path) noexcept{
    if(isEmptyPath(path)) return Dcontext();
}

Dstring Dcontext::path() const noexcept{
    return m_crntPtr -> name;
}

Dstring Dcontext::absolutePath() const noexcept{
    std::vector<Dstring> names;

    auto domain = m_crntPtr;
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

    if(m_crntPtr -> pairs != nullptr){
        auto tail = m_crntPtr -> pairs -> prev;
        tail -> next = newPair;
        newPair -> prev = tail;
        return;
    }

    m_crntPtr -> pairs = newPair;
    newPair -> prev = newPair;
}

void Dcontext::unset(const Dstring &name) noexcept{
    auto pair = findPair(name);
    if(pair == nullptr){
        return;
    }

    auto &head = m_crntPtr -> pairs;

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
    auto nextptr = m_crntPtr -> pairs;

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
        return findDomainFrom(m_crntPtr -> child, names, 0);
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