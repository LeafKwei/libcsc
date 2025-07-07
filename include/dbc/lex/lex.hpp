#ifndef DBC_LEX_HPP
#define DBC_LEX_HPP

#include "dbc/dbc.hpp"

DBC_BEGIN

enum class TokenType{
    Empty,   // Initial type
    Operator, 
    Blank, 
    Other
};

enum class Option{
    Finish,     //Finish this time to read(Character was not be picked, and index was not be increased)
    Pick,        //Pick the character but don't increase the index.
    Forward, //Only increment the index.
    PickAndForward,
    FinishAndForward
}; 

DBC_END
#endif