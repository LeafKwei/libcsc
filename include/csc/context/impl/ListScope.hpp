#ifndef CSC_LISTSCOPE_HPP
#define CSC_LISTSCOPE_HPP

#include <map>
#include <list>
#include "csc/context/Scope.hpp"
CSC_BEGIN

class ListScope : public Scope{
public:
    using ScopePair    = std::pair<String, ScopePtr>;
    using VariablePair = std::pair<String, VariablePtr>;
    using ScopeList    = std::list<ScopePair>;
    using VariableList = std::list<VariablePair>;

public:
    ListScope(const String &name, UID id);
    ListScope(const String &name, UID id, ScopePtr parent);
    bool insertScope(const String &name, ScopePtr sptr) override;
    bool insertVariable(const String &name, VariablePtr vptr) override;
    bool eraseScope(const String &name) override;
    bool eraseVariable(const String &name) override;
    ScopePtr findScope(const String &name) override;
    ScopePtr scope(int index) override;
    VariablePtr findVariable(const String &name) override;
    VariablePtr variable(int index) override;
    ScopePtr parent() override;
    void        setParent(ScopePtr parent) override; 
    Size_t      sizeofScopes() const noexcept override;   
    Size_t      sizeofVariables() const noexcept override;
    bool        noscopes() const noexcept override;
    bool        novariables() const noexcept override;
    ScopeInf scopeinf() const override;   

private:
    ScopeInf         inf_;
    ScopeWptr       parent_;
    ScopeList        scopes_;
    VariableList     variables_;

    ScopeList::iterator     findScopePostion(const String &name);
    VariableList::iterator  findVariablePostion(const String &name);
};

CSC_END
#endif