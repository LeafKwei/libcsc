#ifndef DBC_PATH_HPP
#define DBC_PATH_HPP

#include <vector>
#include <tuple>
#include <array>
#include <cstring>
#include "dbc/dbc.hpp"
#include "dbc/alias.hpp"

DBC_BEGIN

extern const char *builtinPaths[];
std::tuple<Dstring,Dstring> separatePath(const Dstring &path);
std::vector<Dstring> splitPath(const Dstring &path);

//=============== inline ===============
inline bool isEmptyPath(const Dstring &path){ 
    return path.size() == 0; 
}

inline int indexOfBuiltinPath(const Dstring &path){
     for(int index = 0; strlen(builtinPaths[index]) > 0; index++){
        if(path == builtinPaths[index]){
            return index;
        }
    }

    return -1;
}

inline bool isBuiltinPath(const Dstring &path){ 
    return indexOfBuiltinPath(path) != -1;
}

DBC_END
#endif