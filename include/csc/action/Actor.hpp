#ifndef CSC_ACTOR_HPP
#define CSC_ACTOR_HPP

#include "csc/action/types.hpp"
CSC_BEGIN

class Actor{
public:
    Actor(const ActProcessable &proable, const ActProcessor &process, UID scopeid, Livetime livetime=Livetime::Scoped) :
        m_scopeid(scopeid), m_livetime(livetime){}

    UID        scopeID()                                                                { return m_scopeid; }
    Livetime livetime()                                                               { return m_livetime; }

private:
    UID                   m_scopeid;
    Livetime            m_livetime;
};

CSC_END
#endif