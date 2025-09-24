#ifndef CSC_ACTOR_HPP
#define CSC_ACTOR_HPP

#include "csc/action/types.hpp"
CSC_BEGIN

class Actor{
public:
    Actor(const ActProcessable &proable, const ActProcessor &process, UID scopeid, Livetime livetime=Livetime::Scoped) :
        m_scopeid(scopeid), m_livetime(livetime), m_processable(proable), m_processor(process){}

    UID        scopeID()                                      { return m_scopeid; }
    Livetime livetime()                                      { return m_livetime; }
    bool       processable(crAction action) { return m_processable(action); }
    bool       process(crAction action)        { return m_processor(action); }

private:
    UID                   m_scopeid;
    Livetime            m_livetime;
    ActProcessable m_processable;
    ActProcessor    m_processor;
};

CSC_END
#endif