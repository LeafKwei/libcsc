#ifndef CSC_LISTCONTEXT_HPP
#define CSC_LISTCONTEXT_HPP

#include <iostream>
#include <sstream>
#include "csc/csc.hpp"
#include "csc/alias.hpp"
#include "csc/context/types.hpp"
#include "csc/context/Context.hpp"
#include "csc/context/ContextSeeker.hpp"
#include "csc/context/Querier.hpp"
CSC_BEGIN

class ListContext : public Context{
public:
    ListContext();
    ListContext(const ListContext &other) =delete;
    ListContext& operator=(const ListContext &other) =delete;

    ListContext&  makeScope(const String &name, bool entered=false) override;  
    ListContext&  enterScope(const String &name, bool created=false) override;    
    ListContext&  leaveScope() override;                                                                   
    ListContext&  cleanScope(const String &name) override;                                   
    bool          hasScope(const String &name) const override;                        
    bool          isRootScope() const override;                                                         
    Pos            postion() const override;                                                                 
    void           setPostion(const Pos &pos) override;                                             
    Querier      querier(bool absolute=false) const override;                                
    Querier      querier(const String &name) const override;                                

    ListContext&   makeVariable(const String &name, ValueType type, const Value &value) override;      
    ListContext&   makeVariable(const String &name, ValueType type, InitValues values) override; 
    ListContext&   cleanVariable(const String &name) override;                                 
    Unit            getValueUnit(const String &name) const override;                       
    bool           hasVariable(const String &name) const override;                     
    ListContext&   extendValue(const String &name, const Value &value) override;              
    ListContext&   extendValues(const String &name, InitValues values) override;                                                          
    ListContext&   restart() override;                                                                
    void            clean() override;                                                                  
    void            iterate(ContextSeeker &seeker) const override;                 
    const ScopeMetaData&  scopeMetaData() const noexcept override;          

private:
    UID         idCounter_;
    ScopePtr root_;
    ScopePtr current_;

    inline UID nextID() noexcept;
    void do_makeScope(const String &name);
    void do_enterScope(const String &name);
    void do_leaveScope();
    void do_cleanScope(const String &name);
    void do_makeVariable(const String &name, InitValues values, ValueType type);
    void do_cleanVariable(const String &name);
    void do_setVariable(VariablePtr variable, InitValues values, ValueType type);
    void do_iterate(ScopePtr scope, ContextSeeker &seeker) const;
};

inline UID ListContext::nextID() noexcept{
    return idCounter_++;
}

CSC_END
#endif