#ifndef CSC_COMMAND_HPP
#define CSC_COMMAND_HPP

#include <vector>
#include "csc/csc.hpp"
#include "csc/alias.hpp"
#include "csc/syntax/types.hpp"
CSC_BEGIN

class Command{
public:
    using OpType = OperandType;
    using OpTypeList = std::vector<OpType>;
    using TokenList = std::vector<Token>;

public:

    Size_t     sizeofTypes();
    OpType  opTypeAt(int index);
    bool       runable(const TokenList &tokens);                         /* 检查token列表中的token是否是当前命令所需 */
    void       run(const TokenList &tokens, Context &context);

private:
    OpTypeList m_opTypes;
};

CSC_END
#endif