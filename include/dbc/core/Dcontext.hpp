#ifndef DBC_CONTEXT_HPP
#define DBC_CONTEXT_HPP

#include <memory>
#include "dbc/alias.hpp"
#include "dbc/core/Dscope.hpp"
DBC_BEGIN

using DscopePtr = std::shared_ptr<Dscope>;

class Dcontext{
public:
    Dcontext();
    Dcontext(const Dcontext &oth) =delete;
    Dcontext(Dcontext &&oth);
    ~Dcontext();

    bool testScope(const Dstring &path) const noexcept;    /* Test whether a scope is existing. */
    void enterScope(const Dstring &path) noexcept;           /* Enter a existing scope. */
    void beginScope(const Dstring &path) noexcept;          /* Create a scope then enter it. */
    void set(const Dstring &name, const Dstring &value) noexcept;  /* In current scope, set a pair. */
    bool test(const Dstring &name) const noexcept;          /* For current scope, test whether a pair is existring.*/
    Dstring get(const Dstring &name) noexcept;                /* From current scope, get the value for name.*/
    void unset(const Dstring &name);                                 /* For current scope, unset a pair. */
    void endScope() noexcept;                                             /* Exit current socpe and back to its parent scope. */

    Dcontext& operator=(const Dcontext &oth) =delete;
    Dcontext& operator=(Dcontext &&oth);

private:
    Dscope m_rootScope;
    DscopePtr m_rootPtr;
    DscopePtr m_currentPtr;
};


DBC_END
#endif