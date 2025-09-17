#include "csc/types.hpp"
#include "csc/syntax/Command.hpp"
#include "csc/syntax/CmdExecutor.hpp"
CSC_BEGIN

CmdExecutor::CmdExecutor(){
    m_root = std::make_shared<ContNode>();
}

void CmdExecutor::addCommand(CmdPtr cmd){
    if(cmd == nullptr || cmd -> sizeofTokens() == 0) throw CommandExcept("Invalid Command.");
    do_addCommand(m_root, cmd, 0);
}

/* 根据Command对象所需的OperandType找到或创建对应的Node，然后将Command对象保存到Node中 */
void CmdExecutor::do_addCommand(NodePtr node, CmdPtr cmd, Size_t opidx){
    /* 查找当前Node是否存在以opidx对应的OpType为key的Node，如果不存在则创建该Node */
    auto pos = node -> nodes.find(cmd ->opTypeAt(opidx));
    if(pos == node -> nodes.end()){
        auto pair = node -> nodes.insert({cmd ->opTypeAt(opidx), std::make_shared<ContNode>()});
        pos = pair.first;
    }

    /* 如果当前的OpType是最后一个，则保存Command到子Node */
    if(opidx == cmd -> sizeofTokens() - 1){
        pos -> second -> commands.push_back(cmd);
        return;
    }

    /* 如果OpType不是最后一个，则以子Node为基础继续递归 */
    do_addCommand(pos -> second, cmd, opidx + 1);
}

CSC_END