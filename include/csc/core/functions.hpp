#ifndef CSC_CORE_FUNCTIONS_HPP
#define CSC_CORE_FUNCTIONS_HPP

#include <vector>
#include "csc/csc.hpp"
#include "csc/alias.hpp"

CSC_BEGIN

inline std::vector<CscStr> splitPath(ConstStr path){
    std::vector<CscStr> items;
    auto pos = 0;

    if(pos == path.find('/')){                  //If path is starting with '/'
        items.push_back("/");
        ++pos;
    }

    while(pos < path.size()){
        auto nxpos = path.find('/', pos);
        if(nxpos == CscStr::npos){       //If there is no more '/'
            items.push_back(path.substr(pos, path.size() - pos));
            break;
        }

        if(nxpos == pos){                     //If there is a continuous '//'
            items.push_back("");
            pos = nxpos + 1;
            continue;
        }
        
        items.push_back(path.substr(pos, nxpos - pos));
        pos = nxpos + 1;
    }

    return items;
}

inline std::pair<CscStr, CscStr> detachName(ConstStr path){
    auto pos = path.rfind('/');

    if(pos == CscStr::npos){                       //If path is just variable name. e.g. 'age'
        return {"", path};
    }

    if(pos != 0 && pos != path.size() - 1){  //If pos is inside of path.
         return {path.substr(0, pos), path.substr(pos + 1)};
    }

    if(pos == 0 && path.size() > 1){          //If pos is only at start of path.
        return {"/", path.substr(pos + 1)};
    }

    if(pos == path.size() - 1 && path.size() > 1){  //If pos is at end of path.
        return {path.substr(0, pos), ""};
    }

    return {"", ""};
}

CSC_END
#endif