#ifndef CSC_ACTIONHUB_HPP
#define CSC_ACTIONHUB_HPP

#include <list>
#include <map>
#include "csc/action/Actor.hpp"
#include "csc/action/ActionCtl.hpp"
CSC_BEGIN

class ActionHub : public ActionCtl{
public:
    using ActionList = std::list<Action>;
    using ActorList   = std::list<Actor>;
    using ActIterator = ActorList::iterator;
    using ActorMap = std::map<UID, ActorList>;

public:
    void   sendAction(ActionType type, std::any extraData, Context::crMeta meta) override;
    void   sendInnerAction(std::any extraData, Context::crMeta meta) override;
    void   addActor(ActProcessable checker, ActProcessor worker, UID scopeid, Livetime livetime=Livetime::Scoped) override;
    void   distributeAction(Context &context);

private:
    ActionList m_actions;
    ActorMap m_actors;

    void           distributePublicAction(crAction action, Context &context);
    void           distributeInnerAction(crAction action, Context &context);
    void           process_innerExitScope(crAction action, Context &context);
    ActIterator findProcessableActor(ActorList &actorList, crAction action);
    void           removeActor(UID scopeid, Livetime livetime);
};

CSC_END
#endif