#include <cassert>
#include "csc/context/Detector.hpp"
CSC_BEGIN

Detector::Detector(ScopeWkr wkr) : m_ptr(wkr){}

bool Detector::tryEnter(crString name){
    assertValidPtr();
    auto ptr = m_ptr.lock();
    auto pos = ptr -> scopes.find(name);

    if(pos == ptr -> scopes.end()){
        return false;
    }

    m_ptr = pos -> second;
    return true;
}

bool Detector::detect(crString name){
    assertValidPtr();
    return detectScope(name) || detectVariable(name);
}

bool Detector::detectScope(crString name){
    assertValidPtr();
    auto ptr = m_ptr.lock();
     return (ptr -> scopes.find(name) != ptr -> scopes.end());
}

bool Detector::detectVariable(crString name){
    assertValidPtr();
    auto ptr = m_ptr.lock();
     return (ptr -> variables.find(name) != ptr -> variables.end());
}

void Detector::assertValidPtr() const noexcept{
    assert(!m_ptr.expired());
}

CSC_END