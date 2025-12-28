#include <iostream>
#include <fstream>
#include "csc/context/Context.hpp"
#include "csc/core/CscHandler.hpp"
#include "csc/utility/utility.hpp"
using namespace csc;

class AnySeeker : public ContextSeeker{
public:
    void enterScope(UID id, const String &name){
        std::cout << "enter: " << name << ", ID = " << id << std::endl;
    }

    void leaveScope(UID id, const String &name){
        std::cout << "leave: " << name << ", ID = " << id << std::endl;
    }

    void values(const String &name, const Querier &querier){
        std::cout << name <<" = ";
        for(int i = 0; i < querier.querySize(); i++){
            std::cout << valueToString(querier.queryValue(0).value, querier.queryType()) << ",";
        }
        std::cout << std::endl;
    }
};

int main(int argc, char *argv[]){
    std::ifstream ifs("myconfig.csc");
    String str((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());

    AnySeeker seeker;
    CscHandler<ScopeType::MapScope> handler;

    handler.handle(str);
    CscReader reader = handler.reader();
    reader.enter("/custom/tom/");
    std::cout << reader.enterAndGet<int>("age") << std::endl;
    std::cout << reader.enterAndGet<int>("/custom/tom/age") << std::endl;
    std::cout << reader.enterAndGet<String>("/player") << std::endl;
    std::cout << reader.enterAndGet<double>("/custom/tom/height") << std::endl;
    std::cout << reader.enterAndGet<int>("/custom/tom/weight") << std::endl;
    reader.enter("/");
    reader.enter("custom");
    reader.enter("tom");
    std::cout << reader.getValue<bool>("isHappy") << std::endl;
    std::cout << reader.toString() << std::endl;
    std::cout << "========================" << std::endl;
    reader.enter("/");;
    reader.iterate(seeker);
}