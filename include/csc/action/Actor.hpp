#ifndef CSC_ACTOR_HPP
#define CSC_ACTOR_HPP

#include "csc/action/types.hpp"
CSC_BEGIN

class Actor{
public:
    bool processable(ConstAction action);
    bool process(ConstAction action);

private:

};

CSC_END
#endif