#include "dbc/utility/utility.hpp"

DBC_BEGIN

std::tuple<Dstring,Dstring> separate(const Dstring &path) noexcept{
    Dstring prefix;
    Dstring name;

    auto pos = path.find_last_of('/');
    if(pos >= path.size()){
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