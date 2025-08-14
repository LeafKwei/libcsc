#include "dbc/lex/ctrls.hpp"
DBC_BEGIN

//============== TrueCtrl =============
Dstring TrueCtrl::keyword(){
    return "true";
}

void TrueCtrl::changeReaderRule(ReaderBranches &readers){

}

//============== FalseCtrl =============
Dstring FalseCtrl::keyword(){
    return "false";
}

void FalseCtrl::changeReaderRule(ReaderBranches &readers){

}




DBC_END