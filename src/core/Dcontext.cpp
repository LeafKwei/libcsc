#include <algorithm>
#include <cassert>
#include "dbc/core/Dcontext.hpp"
#include "dbc/core/path.hpp"
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

Dcontext::Dcontext(Dcontext &&oth){
    m_rootPtr = oth.m_rootPtr;
    m_crntPtr = oth.m_crntPtr;
    m_lastPtr = oth.m_lastPtr;
    oth.m_rootPtr = nullptr;
    oth.m_crntPtr = nullptr;
    oth.m_lastPtr = nullptr;
}

Dcontext::~Dcontext(){
    m_rootPtr = nullptr;
    m_crntPtr = nullptr;
    m_lastPtr = nullptr;
}

//=============== Operator ===============
Dcontext& Dcontext::operator=(const Dcontext &oth){
    assert(this != std::addressof(oth));    //Use 'addressof' to avoid the case that operator '&' is overloaded.

    m_rootPtr = oth.m_rootPtr;
    m_crntPtr = oth.m_crntPtr;
    m_lastPtr = oth.m_lastPtr;

    return *this;
}

Dcontext& Dcontext::operator=(Dcontext &&oth){
    assert(this != std::addressof(oth));

    m_rootPtr = oth.m_rootPtr;
    m_crntPtr = oth.m_crntPtr;
    m_lastPtr = oth.m_lastPtr;
    oth.m_rootPtr = nullptr;
    oth.m_crntPtr = nullptr;
    oth.m_lastPtr = nullptr;

    return *this;
}

//=============== Public ===============
 bool Dcontext::existsDomain(const Dstring &path) const{
    if(isEmptyPath(path)) return false;
    return findDomain(path) != nullptr;
 }

Derror Dcontext::enterDomain(const Dstring &path){
    if(isEmptyPath(path)) return Derror{ErrorType::Unexcepted, "Empty path."};

    auto ptr = findDomain(path);
    if(ptr != nullptr){
        m_lastPtr = m_crntPtr;
        m_crntPtr = ptr;
        return Derror{ErrorType::OK};
    }

    return Derror{ErrorType::NoSuch, "No such domain."};
}

Derror Dcontext::backDomain(){
    auto tmp = m_crntPtr;
    m_crntPtr = m_lastPtr;
    m_lastPtr = tmp;
    return Derror{ErrorType::OK};
}

Derror Dcontext::makeDomain(const Dstring &path){
    if(isEmptyPath(path)) return Derror{ErrorType::Unexcepted, "Empty path."};
    if(isBuiltinPath(path)) return Derror{ErrorType::Denied, "Can't make built-in domain."};

    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    /* Let we trusts user. OwO
    if(findDomain(path) != nullptr){                                       //If you try to make a repeated domain.
        return Derror{ErrorType::Denied, "Domain exists."};
    }
    */
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

    auto parent = m_crntPtr;
    auto [prefix, name] = separatePath(path);

    if(prefix.size() != 0){
        parent = findDomain(prefix);
        if(parent == nullptr){
            return Derror{ErrorType::NoSuch, "No such path."};
        }
    }

    auto child = std::make_shared<Ddomain>();
    child -> name = name;
    appendChildDomain(parent, child);

    return Derror{ErrorType::OK};
}

Derror Dcontext::makeDomains(const Dstring &path){
    if(isEmptyPath(path)) return Derror{ErrorType::Unexcepted, "Empty path."};
    if(path == "/"){
        return Derror{ErrorType::OK};
    }

    auto [prefix, name] = separatePath(path);
    auto err = makeDomains(prefix);
    
    if(err.type != ErrorType::OK){
        return err;
    }

    return makeDomain(path);
}

Derror Dcontext::dropDomain(const Dstring &path){
    if(isEmptyPath(path)) return Derror{ErrorType::Unexcepted, "Empty path."};

    auto domain = findDomain(path);
    if(domain == nullptr){
        return Derror{ErrorType::NoSuch, "No such path."};
    }

    auto parent = (domain -> parent.lock());
    if(parent == nullptr){
        return Derror{ErrorType::Denied, "Can't drop root domain."};
    }

    updateRelativeDomain(domain);
    removeChildDomain(domain);

    return Derror{ErrorType::OK};
}

Derror Dcontext::exitDomain(){
    auto parent = (m_crntPtr -> parent).lock();
    if(parent == nullptr) return Derror{ErrorType::Denied, "Root reached."};
    m_crntPtr = parent;
    return Derror{ErrorType::OK};
}

Derror Dcontext::attachDomain(const Dstring &path, Dcontext &&context){
    if(isEmptyPath(path)) return Derror{ErrorType::Unexcepted, "Empty path."};
    if(isBuiltinPath(path)) return Derror{ErrorType::Denied, "Can't attach domain on a built-in path."};

    auto parent = m_crntPtr;                   //Relative path is default.
    auto [prefix, name] = separatePath(path);

    if(prefix.size() != 0){                            //If path contains multiple domain
        parent = findDomain(prefix);
        if(parent == nullptr){
            return Derror{ErrorType::NoSuch, "No such path."};
        }
    }

    auto child = context.m_rootPtr;
    child -> name = name;
    child -> parent = parent;

    context.m_rootPtr = nullptr;
    context.m_crntPtr = nullptr;
    context.m_lastPtr = nullptr;

    appendChildDomain(parent, child);
    return Derror{ErrorType::OK};
}

Dcontext Dcontext::detachDomain(const Dstring &path){
    if(isEmptyPath(path)) return Dcontext();

    auto domain = findDomain(path);
    if(domain == nullptr){
        return Dcontext();
    }

    updateRelativeDomain(domain);
    removeChildDomain(domain);

    Dcontext context;
    domain -> name = "/";
    (domain -> parent).reset();    //Let parent be nullptr
    context.m_rootPtr = domain;
    context.m_crntPtr = context.m_rootPtr;
    context.m_lastPtr = context.m_rootPtr;

    return context;
}

Dstring Dcontext::path() const{
    return m_crntPtr -> name;
}

Dstring Dcontext::absolutePath() const{
    std::vector<Dstring> names;

    auto domain = m_crntPtr;
    while(domain != nullptr){
        names.push_back(domain -> name);
        auto parent = (domain -> parent).lock();
        domain = parent;
    }

    std::reverse(names.begin(), names.end());
    return join("/", names, {"/"});    
}

bool Dcontext::exists(const Dstring &name) const{
    return findPair(name) != nullptr;
}

void Dcontext::set(const Dstring &name, const Dstring &value){
    auto pair = findPair(name);
    if(pair != nullptr){
        pair -> value = value;
        return;
    }

    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    /* Release it if you don't want an anonymous pair.
    if(name.size() == 0){      //Can't make anonymous pair.
        return;
    }
    */
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

    auto newPair = std::make_shared<Dpair>();
    newPair -> name = name;
    newPair -> value = value;
    appendPair(m_crntPtr, newPair);
}

void Dcontext::unset(const Dstring &name){
    auto pair = findPair(name);
    if(pair == nullptr){
        return;
    }

    removePair(m_crntPtr, pair);
}

Dstring Dcontext::get(const Dstring &name){
    auto pair = findPair(name);
    if(pair != nullptr){
        return pair -> value;
    }

    return Dstring("");
}

void Dcontext::resetContext(){
    m_rootPtr = nullptr;
    m_crntPtr = nullptr;
    m_lastPtr = nullptr;

    m_rootPtr = std::make_shared<Ddomain>();
    m_rootPtr -> prev = m_rootPtr;
    m_rootPtr -> name = "/";
    m_crntPtr = m_rootPtr;
    m_lastPtr = m_rootPtr;
}

//=============== Private ===============
void Dcontext::appendPair(DdomainPtr &domain, DpairPtr &pair){
    if(domain -> pairs == nullptr){
        domain -> pairs = pair;
        domain -> pairs -> prev = pair;
        return;
    }

    auto tail = (domain -> pairs -> prev).lock();
    tail -> next = pair;
    pair -> prev = tail;
    domain -> pairs -> prev = pair;
}

void Dcontext::removePair(DdomainPtr &parent, DpairPtr &pair){
    if(parent -> pairs == pair){
        parent -> pairs = pair -> next;
        if(parent -> pairs != nullptr){
            parent -> pairs -> prev = pair -> prev;
        }
    }
    else{
        auto before = (pair -> prev).lock();
        auto after = pair -> next;
        before -> next = after;
        if(after != nullptr){
            after -> prev = before;
        }
    }
}

void Dcontext::appendChildDomain(DdomainPtr &parent, DdomainPtr &child){
    child -> parent = parent;

    if(parent -> child == nullptr){
        parent -> child = child;
        parent -> child -> prev = child;
        child -> prev = parent -> child;
        return;
    }

    auto tail = (parent -> child -> prev).lock();
    tail -> next = child;
    child -> prev = tail;
    parent -> child -> prev = child;
}

void Dcontext::removeChildDomain(DdomainPtr &child){
    auto parent = (child -> parent).lock();

    if(parent -> child == child){         //If 'child' is the head of list of child in parent.
        parent -> child = child -> next;
        if(parent -> child != nullptr){
            parent -> child -> prev = child -> prev;
        }
    }
    else{
        auto before = (child -> prev).lock();
        auto after = child -> next;
        before -> next = after;
        if(after != nullptr){
            after -> prev = before;
        }
    }
}

void Dcontext::updateRelativeDomain(DdomainPtr &domain){
    if(domain == m_crntPtr){
        m_crntPtr = (domain -> parent).lock();
    }

    if(domain == m_lastPtr){
        m_lastPtr = m_rootPtr;
    }
}

DpairPtr Dcontext::findPair(const Dstring &name) const{
    auto nextptr = m_crntPtr -> pairs;

    while(nextptr != nullptr){
        if(nextptr -> name == name){
            return nextptr;
        }

        nextptr = nextptr -> next;
    }

    return DpairPtr(nullptr);
}

DdomainPtr Dcontext::findDomain(const Dstring &path) const{
    if(isBuiltinPath(path)) return findBuiltinDomain(path);

    auto names = splitPath(path);
    if(names.at(0) == "/"){
        return findDomainFrom(m_rootPtr -> child, names, 1);
    }
    else{
        return findDomainFrom(m_crntPtr -> child, names, 0);
    }
}

DdomainPtr Dcontext::findBuiltinDomain(const Dstring &path) const{
    switch(indexOfBuiltinPath(path)){
        case 0:  //root
            return m_rootPtr;
        default:
            return DdomainPtr(nullptr);
    }
}

DdomainPtr Dcontext::findDomainFrom(DdomainPtr begin, const std::vector<Dstring> &names, std::size_t pos) const{
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