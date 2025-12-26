#ifndef CSC_MAPCONTEXT_HPP
#define CSC_MAPCONTEXT_HPP

#include <iostream>
#include <sstream>
#include "csc/csc.hpp"
#include "csc/alias.hpp"
#include "csc/context/types.hpp"
#include "csc/context/Context.hpp"
#include "csc/context/ContextSeeker.hpp"
#include "csc/context/Querier.hpp"
CSC_BEGIN

class MapContext : public Context{
public:
    MapContext();
    MapContext(const MapContext &other) =delete;
    MapContext& operator=(const MapContext &other) =delete;

    MapContext&  makeScope(const String &name, bool entered=false) override;  
    MapContext&  enterScope(const String &name, bool created=false) override;    
    MapContext&  leaveScope() override;                                                                   
    MapContext&  cleanScope(const String &name) override;                                   
    bool          hasScope(const String &name) const override;                        
    bool          isRootScope() const override;                                                         
    Pos            postion() const override;                                                                 
    void           setPostion(const Pos &pos) override;                                             
    Querier      querier(bool absolute=false) const override;                                
    Querier      querier(const String &name) const override;                                

    MapContext&   makeVariable(const String &name, ValueType type, const Value &value) override;      
    MapContext&   makeVariable(const String &name, ValueType type, InitValues values) override; 
    MapContext&   cleanVariable(const String &name) override;                                 
    Unit            getValueUnit(const String &name) const override;                       
    bool           hasVariable(const String &name) const override;                     
    MapContext&   extendValue(const String &name, const Value &value) override;              
    MapContext&   extendValues(const String &name, InitValues values) override;                                                          
    MapContext&   restart() override;                                                                
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

inline UID MapContext::nextID() noexcept{
    return idCounter_++;
}

CSC_END
#endif