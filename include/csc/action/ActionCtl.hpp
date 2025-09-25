#ifndef CSC_ACTIONCTL_HPP
#define CSC_ACTIONCTL_HPP

#include <any>
#include "csc/alias.hpp"
#include "csc/action/Action.hpp"
#include "csc/action/types.hpp"
CSC_BEGIN

class ActionCtl{
public:
    virtual void sendAction(ActionType type, std::any extraData, Context::crMeta meta) =0;
    virtual void sendInnerAction(std::any extraData, Context::crMeta meta) =0;
};

CSC_END
#endif