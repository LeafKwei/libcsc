#ifndef CSC_COMMAND_HPP
#define CSC_COMMAND_HPP

#include "csc/csc.hpp"
#include "csc/alias.hpp"
#include "csc/syntax/types.hpp"
CSC_BEGIN

class Command{
public:
    using OpType = OperandType;

public:
    size_t      sizeofTokens();
    OpType  opTypeAt(int index);
};

CSC_END
#endif