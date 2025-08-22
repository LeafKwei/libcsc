#include "csc/core/path.hpp"
CSC_BEGIN

const char *builtinPaths[] = {
    "/"  ,
    ""    //As the end of builtinPaths
};

std::tuple<CscStr,CscStr> separatePath(const CscStr &path){
    CscStr prefix;
    CscStr name;
    auto lastCharPos = path.size() - 1;
    auto size = path.size();

    /* Avoid '/foo/bar/' */
    if(path.find_last_of('/') == lastCharPos){
        --lastCharPos;
        --size;
    }

    /* For 'bar' */
    auto pos = path.find_last_of('/', lastCharPos);
    if(pos == std::string::npos){
        name = path;
        return std::make_tuple(prefix, name);
    }

    /* For '/bar' */
    if(path.find('/') == pos){
        prefix = "/";
        name = (pos + 1) < size ? path.substr(pos + 1, size - pos - 1) : CscStr("");
        return std::make_tuple(prefix, name);
    }

    /* For '/bar/foo' */
    prefix = path.substr(0, pos);
    name = (pos + 1) < path.size() ? path.substr(pos + 1, size - pos -1) : CscStr("");
    return std::make_tuple(prefix, name);
}

std::vector<CscStr> splitPath(const CscStr &path){
    std::vector<CscStr> names;
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

CSC_END