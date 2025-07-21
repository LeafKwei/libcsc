#ifndef DBC_CONTEXT_HPP
#define DBC_CONTEXT_HPP

#include <tuple>
#include <vector>
#include <memory>
#include "dbc/alias.hpp"
#include "dbc/types.hpp"
#include "dbc/core/structs.hpp"
DBC_BEGIN

class Dcontext{
public:
    Dcontext();
    Dcontext(const Dcontext &oth);
    Dcontext(Dcontext &&oth) noexcept;
    ~Dcontext();

    bool existsDomain(const Dstring &path) const noexcept;              /* Test whether a domain is existing. */
    Derror enterDomain(const Dstring &path) noexcept;                     /* Enter a existing domain. */
    Derror backDomain() noexcept;                                                       /* Back to last domain. */
    Derror makeDomain(const Dstring &path) noexcept;                     /* Create a domain. */
    Derror makeDomains(const Dstring &path) noexcept;                   /* Create a domain. Make its parents if they don't exists.*/
    Derror dropDomain(const Dstring &path) noexcept;                      /* Remove an existing domain. */
    Derror exitDomain() noexcept;                                                         /* Exit current domain and back to its parent domain. */
    Derror attachDomain(const Dstring &path, Dcontext &&context) noexcept; /* Attach a context to another context. The attached context will be empty.*/
    Dcontext detachDomain(const Dstring &path) noexcept;               /* Detach a domain from current context. */
    Dstring path() const noexcept;                                                         /* Get current domain name. */
    Dstring absolutePath() const noexcept;                                           /* Get absolute path which begins from root domain to current domain*/
    bool exists(const Dstring &name) const noexcept;                         /* For current domain, test whether a pair is existing.*/
    void set(const Dstring &name, const Dstring &value) noexcept;   /* In current domain, set a pair. */
    void unset(const Dstring &name) noexcept;                                   /* For current domain, unset a pair. */
    Dstring get(const Dstring &name) noexcept;                                 /* From current domain, get the value for name.*/

    Dcontext& operator=(const Dcontext &oth);
    Dcontext& operator=(Dcontext &&oth) noexcept;

private:
    DdomainPtr m_rootPtr;
    DdomainPtr m_crntPtr;
    DdomainPtr m_lastPtr;

    inline void assignPairPrev(DpairPtr &lhs, DpairPtr &rhs);
    inline void assignDomainPrev(DdomainPtr &lhs, DdomainPtr &rhs) const noexcept;
    DpairPtr findPair(const Dstring &name) const noexcept;
    DdomainPtr findDomain(const Dstring &path) const noexcept;
    DdomainPtr findDomainFrom(DdomainPtr begin, const std::vector<Dstring> &names, std::size_t pos) const noexcept;
};


DBC_END
#endif