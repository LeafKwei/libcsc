#include "dbc/utility/utility.hpp"
#include <algorithm>

DBC_BEGIN

Dstring join(Dstring splitor, const std::vector<Dstring> &elements, const std::initializer_list<Dstring> &filters){
    Dstring result;

    for(int idx = 0; idx < elements.size(); idx++){
        auto &e = elements.at(idx);
        result = result + e;
        if(idx + 1 >= elements.size()) continue;                                             //Don't put '/' if 'e' is last element.
        if(std::find(filters.begin(), filters.end(), e) != filters.end()) continue;  //Don't put '/' if 'e' is root.
        result.push_back('/');
    }

    return result;
}

std::tuple<Dstring,Dstring> separate(const Dstring &path) noexcept{
    Dstring prefix;
    Dstring name;

    auto pos = path.find_last_of('/');
    if(pos == std::string::npos){
        name = path;
        return std::make_tuple(prefix, name);
    }

    prefix = path.substr(0, pos);
    name = (pos + 1) < path.size() ? path.substr(pos + 1) : Dstring("");
    return std::make_tuple(prefix, name);
}

std::vector<Dstring> splitPath(const Dstring &path) noexcept{
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


DBC_END