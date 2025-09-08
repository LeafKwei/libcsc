#ifndef CSC_CONTEXT_HPP
#define CSC_CONTEXT_HPP

#include <iostream>
#include <sstream>
#include "csc/csc.hpp"
#include "csc/alias.hpp"
#include "csc/context/types.hpp"
#include "csc/context/ContextSeeker.hpp"
CSC_BEGIN

class Context{
public:
    using Value        = VariableValue;
    using Values      = VariableValues;
    using InitValues = std::initializer_list<CscStr>;
    using Pos           = ScopePos;

public:
    Context();
    Context(const Context &other) =delete;
    Context& operator=(const Context &other) =delete;

    Context& makeScope(ConstStr name, bool entered=false);  /* Make a scope which is child of current scope. Enter it if 'entered' is true. */
    Context& enterScope(ConstStr name, bool created=false);  /* Enter a scope. Create it if 'created' is true. */ 
    Context& leaveScope();                                                         /* Leave current scope, and back to its parent scope. */
    Context& cleanScope(ConstStr name);                                 /* Delete a scope and all variables in it. */
    bool         probeScope(ConstStr name);                                /* Return true if a scope in current scope exists. */
    bool         isAtRootScope();                                                   /* Return true if there is root scope. */
    ConstStr   scopeName();                                                        /* Get current scope's name. */                                    
    Pos           postion();                                                               /* Get postion of current scope. */
    void          setPostion(const Pos &pos);                                /* Set a scope which is specified by pos to current scope. */
    CscStr       relation(ConstStr separator=" ");                          /* Get relation during root scope to current scope. */

    Context& makeVariable(ConstStr name, ConstStr value, ValueType type=ValueType::Unknown);     /* Create a variable. Replace value and type if variable exists. */
    Context& makeVariable(ConstStr name, InitValues values, ValueType type=ValueType::Unknown); /* Put values once. */
    Context& cleanVariable(ConstStr name);                               /* Delete a variable in current socpe. */
    Value        getValue(ConstStr name);                                      /* Get value in a variable. */
    Values      getValues(ConstStr name);                                      /* Get values in a variable */
    bool         probeVariable(ConstStr name);                              /* Return true if a variable in current socpe exists. */
    Context& extendValues(ConstStr name, InitValues values); /* Add values to variable which is specified by name. */
                                                          
    Context& restart();                                                                /* Back to root scope. */
    void clean();                                                                           /* Clean all present scopes, then create a new root scope.*/
    void iterate(ContextSeeker &seeker);                                   /* From current scope, iterate all variables and child scopes with DFS. */

private:
    UID         m_idCounter;
    ScopePtr m_root;
    ScopePtr m_current;

    inline int nextID() noexcept;
    void do_makeScope(ConstStr name);
    void do_enterScope(ConstStr name);
    void do_leaveScope();
    void do_cleanScope(ConstStr name);
    void do_makeVariable(ConstStr name, InitValues values, ValueType type);
    void do_cleanVariable(ConstStr name);
    void do_setVariable(VariablePtr variable, InitValues values, ValueType type);
    void do_iterate(ScopePtr scope, ContextSeeker &seeker);
    void do_relation(ScopePtr scope, std::stringstream &stream, ConstStr separator);
};

inline int Context::nextID() noexcept{
    return m_idCounter++;
}

CSC_END
#endif