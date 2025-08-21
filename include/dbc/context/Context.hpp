#ifndef DBC_CONTEXT_HPP
#define DBC_CONTEXT_HPP

#include "dbc/dbc.hpp"
#include "dbc/alias.hpp"
#include "dbc/context/types.hpp"
#include "dbc/context/ContextSeeker.hpp"
DBC_BEGIN

using ConstVar = const Variable&;
using ConstStr = const Dstring&;

class Context{
public:
    Context() =default;

    Context& makeScope(ConstStr name, bool entered=false);  /* Make a scope which is child of current scope. Enter it if 'entered' is true. */
    Context& enterScope(ConstStr name, bool created=false);  /* Enter a scope. Create it if 'created' is true. */ 
    Context& leaveScope();                                                         /* Leave current scope, and back to its parent scope. */
    Context& cleanScope();                                                         /* Delete a scope and all variables in it. */
    bool         probeScope(ConstStr name);                                /* Return true if a scope exists. */
    ConstStr  scopeName();                                                        /* Get current scope's name. */

    Context& makeVariable(ConstStr name, ConstStr value, ValueType type=ValueType::Unknown); /* Create a variable. Replace value and type if variable exists. */
    Context& cleanVariable(ConstStr name);                               /* Delete a variable. */
    ConstVar  getVariable(ConstStr name);                                  /* Get a variable with const. */
    bool         probeVariable(ConstStr name);                              /* Return true if a variable exists. */
                                                          
    Context& restart();                                                                 /* Back to root scope. */
    Context& clean();                                                                   /* Clean all present scopes, then create a new root scope.*/
    Context& iterate(ContextSeeker &seeker);                           /* Iterate all scope with DFS. */

private:
    ScopePtr m_root;
    ScopePtr m_current;
};

DBC_END
#endif