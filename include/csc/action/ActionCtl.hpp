#ifndef CSC_ACTIONCTL_HPP
#define CSC_ACTIONCTL_HPP

#include <any>
#include "csc/alias.hpp"
#include "csc/action/Action.hpp"
#include "csc/action/types.hpp"
CSC_BEGIN

class ActionCtl{
public:
    virtual void makeActor(const ActProcessable &proable, const ActProcessor &process, Livetime=Livetime::Scoped, const Context &context) =0;
    virtual void sendAction(ActionType type, std::any extraData, const Context &context) =0;
    virtual void sendInnerAction(std::any extraData, const Context &context) =0;
};

CSC_END
#endif