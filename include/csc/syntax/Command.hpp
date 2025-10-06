#ifndef CSC_COMMAND_HPP
#define CSC_COMMAND_HPP

#include <vector>
#include "csc/csc.hpp"
#include "csc/alias.hpp"
#include "csc/lex/types.hpp"
#include "csc/context/Context.hpp"
#include "csc/action/ActionCtl.hpp"
#include "csc/syntax/types.hpp"
CSC_BEGIN

class Command{
public:
    using OpList = std::vector<Operand>;
    using crOpList = const OpList&;

public:
    virtual crString  key() =0;                                                                                       /* 获取此命令的key。key需要根据此命令依赖的Token序列生成。CmdExecuter使用key来归纳和匹配命令 */
    virtual bool       runnable(crOpList operands) =0;                                                /* 检查operand列表中的operand是否是当前命令所需 */
    virtual void       run(crOpList operands, Context &context, ActionCtl &ctl) =0;   /* 使用给定的operand列表、Context对象和ActionCtl对象执行命令 */
};

CSC_END
#endif