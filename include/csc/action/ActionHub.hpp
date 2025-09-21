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
    using ActorMap = std::map<UID, ActionList>;

public:
    void   makeActor(UID scopeid, ActorFunc func, Livetime=Livetime::Scoped) override;
    void   sendAction(UID scopeid, ActionType type, std::any extraData) override;
    void   sendInnerAction(UID scopeid, std::any extraData) override;
    Size_t threshold();
    void   setThreshold(int threshold);
    Size_t sizeofActions();
    void   distributeAction(Context &context);
    void   processInnerAction(Context &context);

private:
    Size_t        m_threshold;  //当Action列表中的Action数量达到多少时，开始分发Action
    ActionList m_actions;
    ActorMap m_actors;
};

CSC_END
#endif