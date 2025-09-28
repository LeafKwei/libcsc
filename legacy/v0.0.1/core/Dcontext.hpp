#ifndef CSC_CONTEXT_HPP
#define CSC_CONTEXT_HPP

#if 0
#include <tuple>
#include <vector>
#include <memory>
#include "csc/alias.hpp"
#include "csc/types.hpp"
#include "csc/core/types.hpp"
#include "csc/core/Dvalue.hpp"
#include "csc/core/Diterator.hpp"
CSC_BEGIN

class Dcontext{
public:
    Dcontext();
    Dcontext(const Dcontext &oth);
    Dcontext(Dcontext &&oth);
    ~Dcontext();

    bool existsDomain(const CscStr &path) const;            /* Test whether a domain is existing. */
    void enterDomain(const CscStr &path);                     /* Enter a existing domain. */
    void backDomain();                                                       /* Back to last domain. */
    void makeDomain(const CscStr &path);                     /* Create a domain. */
    void makeDomains(const CscStr &path);                   /* Create a domain. Make its parents if they don't exists.*/
    void dropDomain(const CscStr &path);                      /* Remove an existing domain. */
    void exitDomain();                                                         /* Exit current domain and back to its parent domain. */
    void attachDomain(const CscStr &path, Dcontext &&context); /* Attach a context to another context. The attached context will be empty.*/
    Dcontext detachDomain(const CscStr &path);               /* Detach a domain from current context. */
    CscStr path() const;                                                         /* Get current domain name. */
    CscStr absolutePath() const;                                           /* Get absolute path which begins from root domain to current domain*/
    bool exists(const CscStr &name) const;                         /* For current domain, test whether a pair is existing.*/
    void set(const CscStr &name, const CscStr &value);   /* In current domain, set a pair. */
    void set(const CscStr &name, const CscStr &value, ValueType type);
    void unset(const CscStr &name);                                   /* For current domain, unset a pair. */
    Dvalue get(const CscStr &name);                                 /* From current domain, get the value for name.*/
    void resetContext();                                                         /* Clean all doamin and pair. */
    void iterate(Diterator &iterator);                                     /* Seek each domain and pair with DFS. */

    Dcontext& operator=(const Dcontext &oth);
    Dcontext& operator=(Dcontext &&oth);

private:
    DdomainPtr m_rootPtr;
    DdomainPtr m_crntPtr;
    DdomainPtr m_lastPtr;

    CscStr makeAbsolutePath(const DdomainPtr &domain) const;
    void appendPair(DdomainPtr &parent, DpairPtr &pair);
    void removePair(DdomainPtr &parent, DpairPtr &pair);
    void appendChildDomain(DdomainPtr &parent, DdomainPtr &child);
    void removeChildDomain(DdomainPtr &child);
    void updateRelativeDomain(DdomainPtr &domain);
    DpairPtr findPair(const CscStr &name) const;
    DdomainPtr findDomain(const CscStr &path) const;
    DdomainPtr findBuiltinDomain(const CscStr &path) const;
    DdomainPtr findDomainFrom(DdomainPtr begin, const std::vector<CscStr> &names, std::size_t pos) const;
    void iterateDomain(DdomainPtr &domain, Diterator &iterator);
};
#endif

#endif