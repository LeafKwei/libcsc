#ifndef CSC_ACTIONCTL_HPP
#define CSC_ACTIONCTL_HPP

#include <any>
#include "csc/alias.hpp"
#include "csc/action/Action.hpp"
#include "csc/action/types.hpp"
CSC_BEGIN

class ActionCtl{
public:
    virtual void sendAction(ActionType type, Any extraData, Context::crScpMeta meta) =0;
    virtual void sendInnerAction(Any extraData, Context::crScpMeta meta) =0;
    virtual void addActor(ActProcessable checker, ActProcessor worker, UID scopeid, Livetime livetime=Livetime::Scoped) =0;
};

CSC_END
#endif