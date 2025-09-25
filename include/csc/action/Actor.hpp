#ifndef CSC_ACTOR_HPP
#define CSC_ACTOR_HPP

#include "csc/action/types.hpp"
CSC_BEGIN

class Actor{
public:
    Actor(const ActProcessable &checker, const ActProcessor &worker, Livetime livetime=Livetime::Scoped) :
        m_livetime(livetime), m_checker(checker), m_worker(worker){}

    Livetime livetime()                                                  { return m_livetime; }
    bool processable(crAction action)                         { return m_checker(action); }
    bool process(crAction action, Context &context)  { return m_worker(action, context); }

private:
    Livetime            m_livetime;
    ActProcessable m_checker;
    ActProcessor    m_worker;
};

CSC_END
#endif