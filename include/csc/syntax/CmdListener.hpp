#ifndef CSC_CMDLISTENER_HPP
#define CSC_CMDLISTENER_HPP

#include <any>
#include <functional>
#include "csc/csc.hpp"
#include "csc/context/Context.hpp"
CSC_BEGIN

enum class ListenerTag{
    ListenMakeScope, ListenMakeVariable
};

struct CmdListener{
    ListenerTag tag;
    std::function<void
    (
        Context &context, 
        const std::any &arg
    )> action; /* 对上下文对象进行处理，arg用于传递一些辅助处理的信息，例如作用域ID */
};

CSC_END
#endif