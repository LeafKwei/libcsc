#ifndef CSC_ACTION_TYPES_HPP
#define CSC_ACTION_TYPES_HPP

#include <functional>
#include "csc/csc.hpp"
CSC_BEGIN

class Action;
using crAction             = const Action&;
using ActProcessable  = std::function<bool(crAction)>;
using ActProcessor     = std::function<bool(crAction)>;

enum class Livetime{
    Oneshot, Scoped
};

enum class ActionType{
    Inner, MakeScope, EnterScope, ExitScope, MakeVariable
};

enum class InnerAction{
    ExitScope
};

CSC_END
#endif