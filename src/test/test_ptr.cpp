#include <memory>
#include <iostream>
#include <algorithm>
#include <string>

struct What{
    What(){
        std::cout << "Ctor" << std::endl;
    }

    ~What(){
        std::cout << "Dctor" << std::endl;
    }
};

int main(void){
    std::shared_ptr<What> sp = std::make_shared<What>();
    sp = nullptr;
    std::cout << "Done..." << std::endl;
}