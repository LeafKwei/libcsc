#include <memory>
#include <iostream>
#include <algorithm>
#include <string>

int main(void){
    std::shared_ptr<int> sp;
    if(sp == nullptr){
        std::cout << "Nullptr" << std::endl;
    }

    std::initializer_list<std::string> il{"A", "B", "C"};
    std::string target = "/";

    if(std::find(il.begin(), il.end(), target));
}