#ifndef CSC_COMMAND_HPP
#define CSC_COMMAND_HPP

#include <vector>
#include "csc/csc.hpp"
#include "csc/alias.hpp"
#include "csc/lex/types.hpp"
#include "csc/context/Context.hpp"
#include "csc/syntax/types.hpp"
CSC_BEGIN

class Command{
public:
    using OpType = OperandType;
    using OpTypeList = std::vector<OpType>;
    using TokenList = std::vector<Token>;

public:
    virtual Size_t     sizeofTypes() =0;                                                             /* 获取OpType的个数 */
    virtual OpType  opTypeAt(int index) =0;                                                 /* 获取指定位置的OpType */
    virtual bool       runnable(const TokenList &tokens) =0;                         /* 检查token列表中的token是否是当前命令所需 */
    virtual void       run(const TokenList &tokens, Context &context) =0;   /* 使用给定的Token序列和Context对象执行命令 */

private:
    OpTypeList m_opTypes;
};

CSC_END
#endif