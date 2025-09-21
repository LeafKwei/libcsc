#ifndef CSC_ACTIONCTL_HPP
#define CSC_ACTIONCTL_HPP

#include <any>
#include "csc/alias.hpp"
#include "csc/action/Action.hpp"
#include "csc/action/types.hpp"
CSC_BEGIN

class ActionCtl{
public:
    virtual void makeActor(UID scopeid, ActorFunc func, Livetime=Livetime::Scoped) =0;
    virtual void sendAction(UID scopeid, ActionType type, std::any extraData) =0;
    virtual void sendInnerAction(UID scopeid, std::any extraData) =0;
};

CSC_END
#endif