#ifndef CSC_MAPSCOPE_HPP
#define CSC_MAPSCOPE_HPP

#include <map>
#include "csc/context/Scope.hpp"
CSC_BEGIN

class MapScope : public Scope{
public:
    using ScopeMap    = std::map<String, ScopePtr>;
    using VariableMap = std::map<String, VariablePtr>;

public:
    MapScope(const String &name, UID id);
    MapScope(const String &name, UID id, ScopePtr parent);
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
    ScopeInf           inf_;
    ScopeWkr         parent_;
    ScopeMap        scopes_;
    VariableMap     variables_;
};

CSC_END
#endif