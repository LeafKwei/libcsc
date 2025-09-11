#ifndef CSC_EVENTCTL_HPP
#define CSC_EVENTCTL_HPP

#include "csc/event/EventHandler.hpp"
#include "csc/event/types.hpp"
CSC_BEGIN

class EventCtl{
public:
    virtual void sendEvent(const Event &event) =0;              /* 发送事件到事件系统并立即处理 */
};

CSC_END
#endif