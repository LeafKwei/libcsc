#ifndef CSC_PURELEXER_HPP
#define CSC_PURELEXER_HPP

#include <vector>
#include "csc/lex/ReaderTree.hpp"
CSC_BEGIN

class PureLexer{
public:
    ReaderTree& tree();

private:
    ReaderTree readertree_;
};

CSC_END

#endif