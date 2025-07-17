#include <iostream>
#include <vector>
#include <string>

using Dstring =std::string;

std::vector<Dstring> splitPath(const Dstring &path){
    std::vector<Dstring> names;
    decltype(path.size()) pos = 0;
    decltype(path.size()) size = path.size();
    
    while(pos < path.size()){
        auto nextPos = path.find('/', pos);
       
        if(nextPos == 0){
            names.push_back("/");
            pos = nextPos + 1;
        }
        else if(nextPos > 0 && nextPos < size){
            if(nextPos == pos){
                names.push_back("");
                pos = nextPos + 1;
            }
            else{
                names.push_back(path.substr(pos, nextPos - pos));
                pos = nextPos + 1;
            }
        }
        else{
            names.push_back(path.substr(pos));
            pos = size;
        }
    }

    return names;
}

int main(void){
    for(auto &p : splitPath("/custom/class")){
        std::cout << "`" << p << "`" << std::endl;
    }

    std::cout << "---------------" << std::endl;

    for(auto &p : splitPath("custom/class")){
        std::cout << "`" << p << "`" << std::endl;
    }

    std::cout << "---------------" << std::endl;

    for(auto &p : splitPath("////")){
        std::cout << "`" << p << "`" << std::endl;
    }
}