#ifndef CSC_CMDCONTAINER_HPP
#define CSC_CMDCONTAINER_HPP

#include <iostream>
#include <csc/alias.hpp>
#include "csc/csc.hpp"
#include "csc/lex/types.hpp"
#include "csc/context/Context.hpp"
#include "csc/syntax/node.hpp"
#include "csc/syntax/CmdListener.hpp"
CSC_BEGIN

class CmdExecutor{
public:
    using CmdPtr  = CommandPtr;
    using NodePtr = ContNodePtr;
    using Tag         = ListenerTag;

public:
    CmdExecutor();
    CmdExecutor(const CmdExecutor &other) =delete;
    CmdExecutor& operator=(const CmdExecutor &other) =delete;

    bool exceed();                                        //是否已到达最后一个Node，即无任何Node可匹配当前的Token列表
    void pushToken(const Token &token);  //压入一个Token到Token列表
    void execute(Context &context);          //使用当前的Token列表和Context对象执行一条命令(即Command对象)
    void addCommand(CmdPtr cmd);        //添加一个Command对象到Node树中
    void addListener(UID scopeid, Tag tag); //todo 将作用域ID和Tag作为一个元组以唯一标识一个Listener。当Leave一个Scope时，ID为该Scope的Listener将被全部移除

private:
    NodePtr m_root;

    void do_addCommand(NodePtr node, CmdPtr cmd, Size_t opidx);
};

CSC_END
#endif