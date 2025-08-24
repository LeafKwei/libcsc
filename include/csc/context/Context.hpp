#ifndef CSC_CONTEXT_HPP
#define CSC_CONTEXT_HPP

#include "csc/csc.hpp"
#include "csc/alias.hpp"
#include "csc/context/types.hpp"
#include "csc/context/ContextSeeker.hpp"
CSC_BEGIN

using ConstVal = const ValueKeeper&;
using ConstStr = const CscStr&;

class Context{
public:
    using Value = VariableValue;
    using Values = VariableValues;

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
    ConstStr  scopeName();                                                        /* Get current scope's name. */

    Context& makeVariable(ConstStr name, ConstStr value, ValueType type=ValueType::Unknown); /* Create a variable. Replace value and type if variable exists. */
    Context& cleanVariable(ConstStr name);                               /* Delete a variable in current socpe. */
    Value        getValue(ConstStr name);                                      /* Get value in a variable. */
    Values      getValues(ConstStr name);                                      /* Get values in a variable */
    bool         probeVariable(ConstStr name);                              /* Return true if a variable in current socpe exists. */
    Context& extendValues(ConstStr name, std::initializer_list<CscStr> values); /* Add values to variable which is specified by name. */
                                                          
    Context& restart();                                                                 /* Back to root scope. */
    Context& clean();                                                                   /* Clean all present scopes, then create a new root scope.*/
    Context& iterate(ContextSeeker &seeker);                           /* From current scope, iterate all variables and child scopes with DFS. */

private:
    ScopePtr m_root;
    ScopePtr m_current;

    void do_makeScope(ConstStr name);
    void do_enterScope(ConstStr name);
    void do_leaveScope();
    void do_cleanScope(ConstStr name);
    void do_makeVariable(ConstStr name, ConstStr value, ValueType type);
    void do_cleanVariable(ConstStr name);
    void do_setVariable(VariablePtr variable, ConstStr value, ValueType type);
    void do_iterate(ScopePtr scope, ContextSeeker &seeker);
};

CSC_END
#endif