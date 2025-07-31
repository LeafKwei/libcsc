#ifndef DBC_CONTEXT_HPP
#define DBC_CONTEXT_HPP

#include <tuple>
#include <vector>
#include <memory>
#include "dbc/alias.hpp"
#include "dbc/types.hpp"
#include "dbc/core/types.hpp"
#include "dbc/core/Dseeker.hpp"
DBC_BEGIN

class Dcontext{
public:
    Dcontext();
    Dcontext(const Dcontext &oth);
    Dcontext(Dcontext &&oth);
    ~Dcontext();

    bool existsDomain(const Dstring &path) const;              /* Test whether a domain is existing. */
    Derror enterDomain(const Dstring &path);                     /* Enter a existing domain. */
    Derror backDomain();                                                       /* Back to last domain. */
    Derror makeDomain(const Dstring &path);                     /* Create a domain. */
    Derror makeDomains(const Dstring &path);                   /* Create a domain. Make its parents if they don't exists.*/
    Derror dropDomain(const Dstring &path);                      /* Remove an existing domain. */
    Derror exitDomain();                                                         /* Exit current domain and back to its parent domain. */
    Derror attachDomain(const Dstring &path, Dcontext &&context); /* Attach a context to another context. The attached context will be empty.*/
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

public:
    template<typename Rt>
    void seekContext(const Dseeker<Rt> &seeker);
};

//=================== Template ==================
template <typename Rt>
void Dcontext::seekContext(const Dseeker<Rt> &seeker){
        
}

DBC_END
#endif