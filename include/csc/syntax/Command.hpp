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

public:

    Size_t     sizeofTokens();
    OpType  opTypeAt(int index);

private:
    OpTypeList m_opTypes;
};

CSC_END
#endif