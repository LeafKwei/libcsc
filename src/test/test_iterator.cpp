#include <iostream>
#include <fstream>
#include "csc/context/Context.hpp"
#include "csc/core/CscStrSeeker.hpp"
#include "csc/syntax/CmdDriver.hpp"
using namespace csc;

int main(void){
    std::ifstream ifs("myconfig.csc");
    CscStr str((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());

    Context context;
    CmdDriver drv;
    CscStrSeeker seeker;
    drv.drive(str, context);

    context.iterate(seeker);
    std::cout << seeker.toString() << std::endl;

    CscStrSeeker seeker2;
    context.enterScope("custom");
    context.iterate(seeker2);
    std::cout << seeker2.toString() << std::endl;
}