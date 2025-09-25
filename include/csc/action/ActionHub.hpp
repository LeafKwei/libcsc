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
    using ActorList = std::list<Actor>;
    using ActorMap = std::map<UID, ActorList>;

public:
    void   sendAction(ActionType type, std::any extraData, Context::crMeta meta) override;
    void   sendInnerAction(std::any extraData, Context::crMeta meta) override;
    Size_t sizeofActions();
    void   distributeAction(Context &context);
    void   processInnerAction(Context &context);

private:
    ActionList m_actions;
    ActorMap m_actors;
};

CSC_END
#endif