#include <cstdio>
#include <iostream>
#include <fstream>
#include "dbc/syntax/CommandDrv.hpp"
using namespace dbc;

int main(void){
    std::ifstream ifs("myconfig.dbc");
    Dstring str((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());

    Dcontext context;
    CommandDrv drv;
    drv.drive(str, context);
}