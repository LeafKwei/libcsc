#if 0
#include <algorithm>
#include <cassert>
#include "csc/core/Dcontext.hpp"
#include "csc/core/path.hpp"
#include "csc/utility/utility.hpp"

CSC_BEGIN

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
 bool Dcontext::existsDomain(const CscStr &path) const{
    if(isEmptyPath(path)) return false;
    return findDomain(path) != nullptr;
 }

void Dcontext::enterDomain(const CscStr &path){
    if(isEmptyPath(path)) throw ContextExcept("Empty path.");

    auto ptr = findDomain(path);
    if(ptr == nullptr) throw ContextExcept("No such domain");
    
    m_lastPtr = m_crntPtr;
    m_crntPtr = ptr;
}

void Dcontext::backDomain(){
    auto tmp = m_crntPtr;
    m_crntPtr = m_lastPtr;
    m_lastPtr = tmp;
}

void Dcontext::makeDomain(const CscStr &path){
    if(isEmptyPath(path)) throw ContextExcept("Empty path.");
    if(isBuiltinPath(path)) throw ContextExcept("Can't make built-in domain.");

    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    /* Let we trusts user. OwO
    if(findDomain(path) != nullptr){                                       //If you try to make a repeated domain.
        throw ContextExcept("Domain exists.");
    }
    */
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

    auto parent = m_crntPtr;
    auto [prefix, name] = separatePath(path);

    if(prefix.size() != 0){
        parent = findDomain(prefix);
        if(parent == nullptr){
            throw ContextExcept("No such path.");
        }
    }

    auto child = std::make_shared<Ddomain>();
    child -> name = name;
    appendChildDomain(parent, child);
}

void Dcontext::makeDomains(const CscStr &path){
    if(isEmptyPath(path)) throw ContextExcept("Empty path.");
    if(path == "/") return;  //No requirement to make root

    auto [prefix, name] = separatePath(path);
    makeDomains(prefix);
    makeDomain(path);
}

void Dcontext::dropDomain(const CscStr &path){
    if(isEmptyPath(path)) throw ContextExcept("Empty path.");

    auto domain = findDomain(path);
    if(domain == nullptr){
        throw ContextExcept("No such path.");
    }

    auto parent = (domain -> parent.lock());
    if(parent == nullptr){
        throw ContextExcept("Can't drop root domain.");
    }

    updateRelativeDomain(domain);
    removeChildDomain(domain);
}

void Dcontext::exitDomain(){
    auto parent = (m_crntPtr -> parent).lock();
    if(parent == nullptr) throw ContextExcept("Root reached.");
    m_crntPtr = parent;
}

void Dcontext::attachDomain(const CscStr &path, Dcontext &&context){
    if(isEmptyPath(path)) throw ContextExcept("Empty path.");
    if(isBuiltinPath(path)) throw ContextExcept("Can't attach domain on a built-in path.");

    auto parent = m_crntPtr;                   //Relative path is default.
    auto [prefix, name] = separatePath(path);

    if(prefix.size() != 0){                            //If path contains multiple domain
        parent = findDomain(prefix);
        if(parent == nullptr){
            throw ContextExcept("No such path.");
        }
    }

    auto child = context.m_rootPtr;
    child -> name = name;
    child -> parent = parent;

    context.m_rootPtr = nullptr;
    context.m_crntPtr = nullptr;
    context.m_lastPtr = nullptr;

    appendChildDomain(parent, child);
}

Dcontext Dcontext::detachDomain(const CscStr &path){
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

CscStr Dcontext::path() const{
    return m_crntPtr -> name;
}

CscStr Dcontext::absolutePath() const{
    return makeAbsolutePath(m_crntPtr);
}

bool Dcontext::exists(const CscStr &name) const{
    return findPair(name) != nullptr;
}

void Dcontext::set(const CscStr &name, const CscStr &value){
    set(name, value, ValueType::Unknown);
}

void Dcontext::set(const CscStr &name, const CscStr &value, ValueType type){
    auto pair = findPair(name);
    if(pair != nullptr){
        pair -> type = type;
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
    newPair -> type = type;
    newPair -> name = name;
    newPair -> value = value;
    appendPair(m_crntPtr, newPair);
}

void Dcontext::unset(const CscStr &name){
    auto pair = findPair(name);
    if(pair == nullptr){
        return;
    }

    removePair(m_crntPtr, pair);
}

Dvalue Dcontext::get(const CscStr &name){
    auto pair = findPair(name);
    if(pair != nullptr){
        return Dvalue(pair -> value, pair -> type);
    }

    return Dvalue("", ValueType::Unknown);
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

void Dcontext::iterate(Diterator &iterator){
    iterateDomain(m_rootPtr, iterator);
}

//=============== Private ===============
CscStr Dcontext::makeAbsolutePath(const DdomainPtr &end) const{
    std::vector<CscStr> names;

    auto domain = end;
    while(domain != nullptr){
        names.push_back(domain -> name);
        auto parent = (domain -> parent).lock();
        domain = parent;
    }

    std::reverse(names.begin(), names.end());
    return join("/", names, {"/"});    
}

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

DpairPtr Dcontext::findPair(const CscStr &name) const{
    auto nextptr = m_crntPtr -> pairs;

    while(nextptr != nullptr){
        if(nextptr -> name == name){
            return nextptr;
        }

        nextptr = nextptr -> next;
    }

    return DpairPtr(nullptr);
}

DdomainPtr Dcontext::findDomain(const CscStr &path) const{
    if(isBuiltinPath(path)) return findBuiltinDomain(path);

    auto names = splitPath(path);
    if(names.at(0) == "/"){
        return findDomainFrom(m_rootPtr -> child, names, 1);
    }
    else{
        return findDomainFrom(m_crntPtr -> child, names, 0);
    }
}

DdomainPtr Dcontext::findBuiltinDomain(const CscStr &path) const{
    switch(indexOfBuiltinPath(path)){
        case 0:  //root
            return m_rootPtr;
        default:
            return DdomainPtr(nullptr);
    }
}

DdomainPtr Dcontext::findDomainFrom(DdomainPtr begin, const std::vector<CscStr> &names, std::size_t pos) const{
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

void Dcontext::iterateDomain(DdomainPtr &domain, Diterator &iterator){
    if(domain != m_rootPtr){                    //Don't pass root domain's name.
        iterator.enter(domain -> name);
    }

    auto pair = domain -> pairs;
    while(pair != nullptr){
        iterator.pair(pair -> name, pair -> value, pair -> type);
        pair = pair -> next;
    }

    auto child = domain -> child;
    if(child != nullptr){
        iterateDomain(child, iterator);
    }

    if(domain != m_rootPtr){
        iterator.exit(domain -> name);
    }

    auto bro = domain -> next;
    while(bro != nullptr){
        iterateDomain(bro, iterator);
        bro = bro -> next;
    }
}

CSC_END
#endif