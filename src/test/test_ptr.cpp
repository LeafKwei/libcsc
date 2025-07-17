#include <memory>
#include <iostream>

int main(void){
    std::shared_ptr<int> sp;
    if(sp == nullptr){
        std::cout << "Nullptr" << std::endl;
    }
}