#include <iostream>
#include <fstream>
#include "csc/core/CscHandler.hpp"
using namespace csc;

class AnySeeker : public ContextSeeker{
public:
    void enterScope(const CscStr &name){
        std::cout << "enter: " << name << std::endl;
    }

    void leaveScope(const CscStr &name){
        std::cout << "leave: " << name << std::endl;
    }

    void values(const CscStr &name, const VariableValues &values){
        std::cout << "value: " << values.str() << std::endl;
    }
};

int main(int argc, char *argv[]){
    std::ifstream ifs("myconfig.csc");
    CscStr str((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());

    AnySeeker seeker;
    CscHandler handler(str);

    std::cout << handler.enterAndGet<int>("/custom/tom/age") << std::endl;
    std::cout << handler.enterAndGet<CscStr>("/player") << std::endl;
    std::cout << handler.enterAndGet<double>("/custom/tom/height") << std::endl;
    std::cout << handler.enterAndGet<int>("/custom/tom/weight") << std::endl;
    std::cout << handler.enter("/").enter("custom").enter("tom").getValue<bool>("isHappy") << std::endl;
    //std::cout << handler.enter("/").toString() << std::endl;
    //handler.enter("/").iterate(seeker);
}