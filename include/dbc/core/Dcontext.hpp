#ifndef DBC_CONTEXT_HPP
#define DBC_CONTEXT_HPP

#include <tuple>
#include <vector>
#include <memory>
#include "dbc/alias.hpp"
#include "dbc/types.hpp"
#include "dbc/core/types.hpp"
DBC_BEGIN

class Dcontext{
public:
    Dcontext();
    Dcontext(const Dcontext &oth);
    Dcontext(Dcontext &&oth);
    ~Dcontext();

    bool existsDomain(const Dstring &path) const;              /* Test whether a domain is existing. */
    void enterDomain(const Dstring &path);                     /* Enter a existing domain. */
    void backDomain();                                                       /* Back to last domain. */
    void makeDomain(const Dstring &path);                     /* Create a domain. */
    void makeDomains(const Dstring &path);                   /* Create a domain. Make its parents if they don't exists.*/
    void dropDomain(const Dstring &path);                      /* Remove an existing domain. */
    void exitDomain();                                                         /* Exit current domain and back to its parent domain. */
    void attachDomain(const Dstring &path, Dcontext &&context); /* Attach a context to another context. The attached context will be empty.*/
    Dcontext detachDomain(const Dstring &path);               /* Detach a domain from current context. */
    Dstring path() const;                                                         /* Get current domain name. */
    Dstring absolutePath() const;                                           /* Get absolute path which begins from root domain to current domain*/
    bool exists(const Dstring &name) const;                         /* For current domain, test whether a pair is existing.*/
    void set(const Dstring &name, const Dstring &value);   /* In current domain, set a pair. */
    void unset(const Dstring &name);                                   /* For current domain, unset a pair. */
    Dstring get(const Dstring &name);                                 /* From current domain, get the value for name.*/
    void resetContext();

    Dcontext& operator=(const Dcontext &oth);
    Dcontext& operator=(Dcontext &&oth);

private:
    DdomainPtr m_rootPtr;
    DdomainPtr m_crntPtr;
    DdomainPtr m_lastPtr;

    void appendPair(DdomainPtr &parent, DpairPtr &pair);
    void removePair(DdomainPtr &parent, DpairPtr &pair);
    void appendChildDomain(DdomainPtr &parent, DdomainPtr &child);
    void removeChildDomain(DdomainPtr &child);
    void updateRelativeDomain(DdomainPtr &domain);
    DpairPtr findPair(const Dstring &name) const;
    DdomainPtr findDomain(const Dstring &path) const;
    DdomainPtr findBuiltinDomain(const Dstring &path) const;
    DdomainPtr findDomainFrom(DdomainPtr begin, const std::vector<Dstring> &names, std::size_t pos) const;
};

DBC_END
#endif