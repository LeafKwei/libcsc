#ifndef CSC_ACTION_TYPES_HPP
#define CSC_ACTION_TYPES_HPP

#include <functional>
#include "csc/csc.hpp"
CSC_BEGIN

class Action;
using ConstAction = const Action&;
using ActorFoo  = std::function<bool(ConstAction)>;
using ActorFunc = std::function<bool(ConstAction)>;

enum class Livetime{
    OneShot, Scoped
};

enum class ActionType{
    Inner, MakeScope, EnterScope, ExitScope, MakeVariable
};

enum class InnerAction{
    ExitScope
};

CSC_END
#endif