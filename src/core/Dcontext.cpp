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

    return *this;
}

Dcontext& Dcontext::operator=(Dcontext &&oth) noexcept{
    assert(this != &oth);

    m_rootPtr = oth.m_rootPtr;
    m_crntPtr = oth.m_crntPtr;
    m_lastPtr = oth.m_lastPtr;
    oth.m_rootPtr = nullptr;
    oth.m_crntPtr = nullptr;
    oth.m_lastPtr = nullptr;

    return *this;
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
    return Derror{ErrorType::OK};
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

    auto newDomain = std::make_shared<Ddomain>();
    newDomain -> name = name;
    appendChildDomain(m_crntPtr, newDomain);

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

    removeChildDomain(domain);

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

    auto domain = context.m_rootPtr;
    context.m_rootPtr = nullptr;
    context.m_crntPtr = nullptr;
    context.m_lastPtr = nullptr;

    domain -> name = name;
    appendChildDomain(m_crntPtr, domain);
    backDomain();
    return Derror{ErrorType::OK};
}

Dcontext Dcontext::detachDomain(const Dstring &path) noexcept{
    if(isEmptyPath(path)) return Dcontext();

    auto domain = findDomain(path);
    if(domain == nullptr){
        return Dcontext();
    }

    removeChildDomain(domain);

    Dcontext context;
    domain -> name = "/";
    context.m_rootPtr = domain;
    context.m_crntPtr = context.m_rootPtr;
    context.m_lastPtr = context.m_rootPtr;

    return context;
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

    removePair(m_crntPtr, pair);
}

Dstring Dcontext::get(const Dstring &name) noexcept{
    auto pair = findPair(name);
    if(pair != nullptr){
        return pair -> value;
    }

    return Dstring("");
}

//=============== Private ===============
void Dcontext::appendPair(DdomainPtr &domain, DpairPtr &pair) noexcept{
    if(domain -> pairs == nullptr){
        domain -> pairs = pair;
        domain -> pairs -> prev = pair;
        pair -> prev = domain -> pairs;
        return;
    }

    auto &tail = domain -> pairs -> prev;
    tail -> next = pair;
    pair -> prev = tail;
    domain -> pairs -> prev = pair;
}

void Dcontext::removePair(DdomainPtr &parent, DpairPtr &pair) noexcept{
    if(parent -> pairs == pair){
        parent -> pairs = pair -> next;
        if(parent -> pairs != nullptr){
            parent -> pairs -> prev = pair -> prev;
        }
    }
    else{
        auto &before = pair -> prev;
        auto &after = pair -> next;
        before -> next = after;
        if(after != nullptr){
            after -> prev = before;
        }
    }
}

void Dcontext::appendChildDomain(DdomainPtr &parent, DdomainPtr &child) noexcept{
    child -> parent = parent;

    if(parent -> child == nullptr){
        parent -> child = child;
        parent -> child -> prev = child;
        child -> prev = parent -> child;
        return;
    }

    auto &tail = parent -> child -> prev;
    tail -> next = child;
    child -> prev = tail;
    parent -> child -> prev = child;
}

void Dcontext::removeChildDomain(DdomainPtr &child) noexcept{
    auto &parent = child -> parent;

    if(parent -> child == child){         //If 'child' is the head of list of child in parent.
        parent -> child = child -> next;
        if(parent -> child != nullptr){
            parent -> child -> prev = child -> prev;
        }
    }
    else{
        auto &before = child -> prev;
        auto &after = child -> next;
        before -> next = after;
        if(after != nullptr){
            after -> prev = before;
        }
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