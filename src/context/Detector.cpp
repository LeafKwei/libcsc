#include <cassert>
#include "csc/context/Detector.hpp"
CSC_BEGIN

Detector::Detector(ScopeWkr wkr) : ptr_(wkr){}

bool Detector::tryEnter(crString name){
    assertValidPtr();
    auto ptr = ptr_.lock();
    auto pos = ptr -> scopes.find(name);

    if(pos == ptr -> scopes.end()){
        return false;
    }

    ptr_ = pos -> second;
    return true;
}

bool Detector::detect(crString name){
    assertValidPtr();
    return detectScope(name) || detectVariable(name);
}

bool Detector::detectScope(crString name){
    assertValidPtr();
    auto ptr = ptr_.lock();
     return (ptr -> scopes.find(name) != ptr -> scopes.end());
}

bool Detector::detectVariable(crString name){
    assertValidPtr();
    auto ptr = ptr_.lock();
     return (ptr -> variables.find(name) != ptr -> variables.end());
}

void Detector::assertValidPtr() const noexcept{
    assert(!ptr_.expired());
}

CSC_END